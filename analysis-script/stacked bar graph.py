import matplotlib.pyplot as plt
import numpy as np

# data from https://allisonhorst.github.io/palmerpenguins/

machines = (
    "PC1",#iot
    "PC2",#elite
    "PC3",#think
)
pkgcores = np.array([25.25, 26.78,29.25])
ram = np.array([44.75, 43.16,29.25])
psys = np.array([53.1, 50.81, 29.25])

weight_counts = {
    "Pkg+Cores": pkgcores,
    "Pkg+Cores+RAM": ram - pkgcores,
    "Pkg+Cores+RAM+PSys": psys - ram,
}
width = 0.5

fig, ax = plt.subplots()
bottom = np.zeros(3)

for boolean, weight_count in weight_counts.items():
    p = ax.bar(machines, weight_count, width, label=boolean, bottom=bottom)
    bottom += weight_count

ax.set_title("Classification Accuracy Using RAPL Energy Domains (flag -O2)")
ax.legend(loc="upper right")
plt.ylabel('Percentage Correctly Classified')

plt.show()