import random

solutions_per_page = 30

page_first_solution = int(input("Page of the first C++ solution: "))

page_last_solution = int(input("Page of the last C++ solution: "))

n_solutions = int(input("Number of solutions to gather: "))

solutions = []
for _ in range(n_solutions):
  page = random.randint(page_first_solution, page_last_solution)
  solution = random.randint(1, solutions_per_page)
  solutions.append([page, solution])
  
for sol in sorted(solutions):
  print(f"{sol[0]} {sol[1]}")
