change = 2780
n500, n100, n50, n10 = 0, 0, 0, 0

while (change >= 500):
    change -= 500
    n500 += 1

while (change >= 100):
    change -= 100
    n100 += 1

while (change >= 50):
    change -= 50
    n50 += 1

while (change >= 10):
    change -= 10
    n10 += 1
    
print(f"- 2780 Won - 500 Won: {n500}, 100 Won: {n100}, 50 Won: {n50}, 10 Won: {n10}")
