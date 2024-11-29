c = 10 # 배낭의 용량 10kg
n = 4 # 물건 개수
weights = [5, 4, 6, 3] # 물건 i의 무게
values = [10, 40, 30, 50] # 물건 i의 가치

# 테이블 초기화 (배낭의 무게 0~c 까지, 물건 개수 0~n까지)
k = [[0 for _ in range(c+1)] for _ in range(n+1)] 

# 테이블 채우기
for i in range(n) :
    k[i][0] = 0
for W in range(c):
    k[0][W] = 0
for i in range(1, n+1):
    for W in range(c+1):
        if weights[i - 1] > W:
            k[i][W] = k[i-1][W]
        else:
            k[i][W] = max(k[i-1][W], k[i-1][W-weights[i-1]] + values[i - 1])

# 테이블 출력
print("  배낭 용량 -> w =  ", end="")
for W in range(c + 1):
    print(f"{W:4}", end="")
print()
print("-" * (5 * (c + 3)))

for i in range(n + 1):
    if i == 0:
        print("물건 | 가치 | 무게 |", end="")
    else:
        print(f"  {i}  |  {values[i - 1]:2}  |  {weights[i - 1]:2}  |", end="")
    for W in range(c + 1):
        print(f"{k[i][W]:4}", end="")
    print()

# 최적해 출력
print(f"\n최적해 K[{n}][{c}] = {k[n][c]}")
