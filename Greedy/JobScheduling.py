import time

t1 = [7, 8]
t2 = [3, 7]
t3 = [1, 5]
t4 = [5, 9]
t5 = [0, 2]
t6 = [6, 8]
t7 = [1, 6]
# 작업을 리스트 L에 담기
L = [t1, t2, t3, t4, t5, t6, t7]

time_slots = 10
machines = []

start_time = time.time()

# 시작 시간 기준으로 정렬
L_sorted = sorted(L, key=lambda x: x[0])

# L_sorted이 공집합이 될 때까지 반복
while L_sorted:
    task = L_sorted.pop(0) #첫번째 작업을 가져오고 리스트에서는 제거
    start, end = task
    task_name = f"t{L.index(task) + 1}" #작업명 저장

    # 머신 동작 여부
    assigned = False

    # 기존 머신에 작업 할당
    for machine in machines:
        if all(slot is None for slot in machine[start:end]):
            for i in range(start,end): 
                machine[i] = task_name 
            assigned = True
            break

    # 작업을 할당할 수 있는 머신이 없으면 새로운 머신 추가
    if not assigned:
        new_machine = [None] * time_slots
        for i in range(start, end):
            new_machine[i] = task_name
        machines.append(new_machine)

end_time = time.time()

print(f"실행 시간: {end_time - start_time:.6f} 초")

# 머신 스케줄링 결과 출력
# 데이터 생성
data = {'Time': list(range(time_slots))}
for idx, machine in enumerate(machines):
    data[f'Machine {idx + 1}'] = machine

# 스케줄링 결과 가로로 출력
print("\nTask Scheduling Table:")
print("Time", end="\t")
for i in range(time_slots):
    print(i, end="\t")
print()

for machine_name in reversed(list(data.keys())):
    if machine_name != 'Time':
        print(machine_name, end="\t")
        for i in range(time_slots):
            print(data[machine_name][i] if data[machine_name][i] is not None else '', end="\t")
        print()