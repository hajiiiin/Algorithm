import math
import time

# 두 점 사이 거리 구하는 함수
def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

# 점이 3개 이하일 때 brute-force 방식으로 점 사이 거리 찾기
def brute_force(points):
    min_dist = float('inf')
    pair = None
    n = len(points)
    for i in range(n):
        for j in range(i + 1, n):
            dist = distance(points[i], points[j])
            if dist < min_dist:
                min_dist = dist
                pair = (points[i], points[j])
    return min_dist, pair

# y축 기준으로 최소 거리(d) 찾기
def strip_closest(strip, d):
    min_dist = d
    n = len(strip)
    strip.sort(key=lambda point: point[1])  # Sort by y-coordinate
    for i in range(n):
        for j in range(i + 1, n):
            if (strip[j][1] - strip[i][1]) < min_dist:
                dist = distance(strip[i], strip[j])
                if dist < min_dist:
                    min_dist = dist
    return min_dist

def closest_pair(points):
    points.sort() # x좌표 정렬

    # 리스트가 비어 있거나 1개일 경우 종료 조건 추가
    if len(points) < 2:
        return float('inf'), None
    
    if len(points) <= 3:
        brute_force(points)

    mid = len(points) // 2
    mid_point = points[mid]

    dl, pair_l = closest_pair(points[:mid])
    dr, pair_r = closest_pair(points[mid:])

    # dl과 dr 중 최소 거리를 d로 정함, 최소 거리인 쌍을 pair에 저장
    d = min(dl, dr)
    pair = pair_l if dl < dr else pair_r
    
    # 중간 경계선 근처에 있는 점들을 모아서 strip에 저장
    strip = [p for p in points if abs(p[0] - mid_point[0]) < d]

    ds = strip_closest(strip, d)

    if ds < d:
        return ds, pair
    else:
        return d, pair
    

# input 파일 읽어오기
def read_input(file_name):
    points = []
    with open(file_name, 'r') as file:
        for line in file:
            x, y = map(int, line.split())
            points.append((x, y))
    return points

if __name__ == "__main__":
    input_file = "input_closest_pair.txt"
    points = read_input(input_file)
    
    start_time = time.time()
    min_dist, pair = closest_pair(points)
    end_time = time.time()
    
    print(f"최단 거리: {min_dist}")
    print(f"좌표 쌍: {pair}")
    print(f"실행 시간: {end_time - start_time:.6f} 초")
