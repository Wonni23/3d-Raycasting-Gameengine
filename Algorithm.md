# Cub3D 알고리즘 분석

이 문서에서는 `cub3D` 프로젝트의 핵심이 되는 두 가지 주요 알고리즘, 레이캐스팅(Raycasting)과 스프라이트 렌더링(Sprite Rendering)에 대해 설명합니다.

## 1. 레이캐스팅 (Raycasting)

레이캐스팅은 2D 맵 데이터를 사용하여 3D와 같은 시각적 효과를 만들어내는 렌더링 기술입니다. 플레이어의 시점에서 화면의 모든 수직선(column)에 대해 광선(ray)을 쏘아, 광선이 벽에 닿는 지점을 계산하고 그 거리에 따라 벽의 크기를 조절하여 화면에 그립니다.

이 프로젝트의 레이캐스팅은 다음 단계로 이루어집니다. (`src/rendering/raycasting.c` 참고)

### 1.1. 광선 설정 (Setup)

- 화면의 각 픽셀 열(column `x`)에 대해 광선을 계산합니다.
- **카메라 공간 `camera_x`**: 현재 `x` 좌표를 `-1` (화면 왼쪽 끝)에서 `1` (화면 오른쪽 끝) 사이의 값으로 정규화합니다.
- **광선 방향 `ray_dir`**: 플레이어의 현재 방향 벡터(`dir`)와 카메라 평면 벡터(`plane`)를 조합하여 현재 `x` 열에 대한 광선의 방향 벡터를 계산합니다.

```c
// raycasting_setup.c
ray->camera_x = 2 * x / (double)WIDTH - 1;
ray->ray_dir_x = cub->player.dir_x + cub->player.plane_x * ray->camera_x;
ray->ray_dir_y = cub->player.dir_y + cub->player.plane_y * ray->camera_x;
```

### 1.2. DDA 알고리즘 (Digital Differential Analysis)

- **DDA**는 광선이 맵의 격자를 따라 이동하며 벽과 만나는 지점을 찾는 알고리즘입니다.
- **`delta_dist`**: 광선이 x 또는 y 방향으로 한 칸 이동할 때 필요한 실제 거리입니다. 피타고라스 정리에 따라 계산되며, `ray_dir`이 0일 때 무한대가 되는 것을 방지하기 위해 예외 처리를 합니다.
- **`side_dist`**: 플레이어 위치에서 출발하여 처음으로 x 또는 y 격자선과 만날 때까지의 광선의 이동 거리입니다.
- **`step`**: 광선이 어느 방향(+, -)으로 진행하는지를 나타내는 정수 값입니다.

DDA 루프는 `side_dist_x`와 `side_dist_y` 중 더 작은 값을 선택하여 광선을 해당 방향으로 한 칸 전진시킵니다. 이 과정을 벽(`map[y][x] == '1'`)에 부딪힐 때까지 반복합니다.

```c
// raycasting.c -> perform_dda()
while (!ray->hit)
{
    if (ray->side_dist_x < ray->side_dist_y)
    {
        ray->side_dist_x += ray->delta_dist_x;
        ray->map_x += ray->step_x;
        ray->side = WALL_X; // X축 격자선과 충돌
    }
    else
    {
        ray->side_dist_y += ray->delta_dist_y;
        ray->map_y += ray->step_y;
        ray->side = WALL_Y; // Y축 격자선과 충돌
    }
    if (map[ray->map_y][ray->map_x] == '1')
        ray->hit = 1;
}
```

### 1.3. 거리 계산 및 어안 렌즈 효과(Fisheye Effect) 보정

- 광선이 벽에 부딪히면, 플레이어 위치에서 벽까지의 유클리드 거리 대신 **수직 거리**(`perp_wall_dist`)를 계산합니다.
- 이는 플레이어 시점과 벽 사이의 직선 거리가 아닌, 카메라 평면에 수직으로 투영된 거리를 의미합니다. 이 값을 사용해야 벽이 중앙에서 멀어질수록 왜곡되어 보이는 어안 렌즈 효과를 방지하고, 모든 벽이 수직으로 보이게 됩니다.

```c
// raycasting.c -> perform_dda()
if (ray->side == WALL_X)
    ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
else
    ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
```

### 1.4. 벽 높이 및 텍스처 계산

- 계산된 수직 거리를 사용하여 화면에 그려질 벽의 높이(`line_height`)를 계산합니다. 거리가 멀수록 높이는 낮아집니다.
- 광선이 벽의 어느 지점(`wall_x`)에 부딪혔는지 계산하여, 해당 위치에 매핑될 텍스처의 x좌표(`tex_x`)를 결정합니다.
- 화면에 벽을 그릴 때, 계산된 `line_height`에 맞춰 텍스처의 y좌표(`tex_y`)를 비례적으로 증가시키며 픽셀 색상을 가져와 버퍼에 저장합니다.

---

## 2. 2D 스프라이트 렌더링 (보너스)

보너스 파트에서는 적(enemy)과 같은 2D 이미지를 3D 공간에 배치하는 스프라이트 렌더링을 구현합니다. 핵심은 **행렬 변환**을 통해 스프라이트의 월드 좌표를 카메라 좌표로 변환하는 것입니다.

이 과정은 다음 단계로 이루어집니다. (`src/bonus/enemy_set_bonus.c`, `src/bonus/enemy_draw_bonus.c` 참고)

### 2.1. 스프라이트 정보 수집 및 정렬

1.  맵을 순회하며 모든 스프라이트(적)의 위치를 찾습니다.
2.  각 스프라이트와 플레이어 간의 거리를 계산합니다.
3.  스프라이트를 **플레이어로부터 먼 순서대로 정렬**(sort)합니다. 이는 반투명 스프라이트나 복잡한 장면에서 올바른 렌더링 순서를 보장하기 위함입니다. (Painter's Algorithm)

```c
// enemy_set_bonus.c -> sort_sprites()
// 거리를 기준으로 버블 정렬을 사용하여 내림차순으로 정렬합니다.
if (sprites[j].distance < sprites[j + 1].distance)
{
    // swap
}
```

### 2.2. 좌표 변환 (행렬 변환)

- 정렬된 각 스프라이트에 대해 월드 좌표를 카메라 시점 좌표계로 변환합니다. 이 과정은 **카메라 역행렬**(Inverse Camera Matrix)을 사용하여 수행됩니다.
- **스프라이트 상대 좌표**: `(sprite_x, sprite_y) = (sprite.x - player.x, sprite.y - player.y)`
- **카메라 행렬**: `[dir_x, plane_x]` 와 `[dir_y, plane_y]` 로 구성된 2x2 행렬입니다.
- **역행렬 계산**:
  ```
  inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y)
  ```
- **좌표 변환**:
  - `transform_x`: 카메라 공간에서의 x좌표. 화면의 수평 위치를 결정합니다.
  - `transform_y`: 카메라 공간에서의 y좌표 (깊이). 화면에서의 크기와 렌더링 여부를 결정합니다.

```c
// enemy_set_bonus.c -> transform_sprites()
// 스프라이트 위치를 플레이어 기준으로 변환
sprite_x = sprites[i].x - cub->player.pos_x;
sprite_y = sprites[i].y - cub->player.pos_y;

// 카메라 역행렬의 행렬식 역수
inv_det = 1.0 / (cub->player.plane_x * cub->player.dir_y - \
    cub->player.dir_x * cub->player.plane_y);

// 행렬 곱셈을 통해 카메라 공간 좌표로 변환
sprites[i].transform_x = inv_det * (cub->player.dir_y * sprite_x - \
    cub->player.dir_x * sprite_y);
sprites[i].transform_y = inv_det * (-cub->player.plane_y * sprite_x + \
    cub->player.plane_x * sprite_y);
```

이 변환을 통해 `transform_y`는 카메라 앞뒤 거리가 되고, `transform_x`는 카메라 평면 기준 좌우 위치가 됩니다.

### 2.3. 스프라이트 화면 좌표 및 크기 계산

- 변환된 `transform_x`와 `transform_y`를 사용하여 스프라이트가 화면의 어느 위치(`screen_x`)에, 어느 정도의 크기(`width`, `height`)로 그려질지 계산합니다.
- `transform_y` (깊이)가 작을수록 (가까울수록) 스프라이트는 더 크게 그려집니다.

```c
// enemy_set_bonus.c -> transform_sprites()
sprites[i].screen_x = (int)((WIDTH / 2) * \
    (1 + sprites[i].transform_x / sprites[i].transform_y));
sprites[i].width = abs((int)(HEIGHT / sprites[i].transform_y));
```

### 2.4. 렌더링 및 Z-버퍼링

- 계산된 화면 위치와 크기에 따라 스프라이트를 그립니다.
- 이때 **Z-버퍼(Z-buffer)** 또는 깊이 버퍼(`z_buffer`)를 사용합니다. Z-버퍼는 레이캐스팅 단계에서 계산된 각 화면 열의 벽까지의 거리를 저장하고 있는 배열입니다.
- 스프라이트의 특정 수직선(`stripe`)을 그리기 전에, 해당 `stripe`의 `transform_y` (깊이) 값과 Z-버퍼에 저장된 벽의 거리를 비교합니다.
- **스프라이트가 벽보다 앞에 있을 경우에만 해당 픽셀을 그립니다.** 이를 통해 스프라이트가 벽 뒤에 가려지는 효과를 올바르게 구현할 수 있습니다.

```c
// enemy_draw_bonus.c -> render_single_sprite()
while (stripe < draw_end_x)
{
    // transform_y (깊이)가 0보다 크고(카메라 앞에 있고),
    // z_buffer에 저장된 벽의 거리보다 가까우면 렌더링
    if (sprite.transform_y > 0 && sprite.transform_y <= z_buffer[stripe])
        render_sprite_stripe(cub, sprite, stripe);
    stripe++;
}
```

이러한 과정을 통해 2D 이미지가 3D 공간 안에 자연스럽게 배치된 것처럼 보이게 됩니다.
