import sys
import numpy as np
import matplotlib.pyplot as plt

save = "-p" in sys.argv

n = 200
p = 0.01
q = 1 - p
k1 = 3
k2 = 5

mu = n * p
sigma = np.sqrt(n * p * q)
x1 = (k1 - mu) / sigma
x2 = (k2 - mu) / sigma

x = np.linspace(-4, 4, 1000)
phi = (1 / np.sqrt(2 * np.pi)) * np.exp(-x**2 / 2)

fig, ax = plt.subplots(figsize=(10, 6))
ax.plot(x, phi, linewidth=2)
ax.fill_between(x, phi, where=(x >= x1) & (x <= x2), color="#1f77b4", alpha=1)
ax.axvline(x1, linewidth=1.5)
ax.axvline(x2, linewidth=1.5)

ax.text(x1, max(phi) * 0.5, rf"$x_1$", ha="right", va="center", fontsize=12)
ax.text(x2, max(phi) * 0.5, rf"$x_2$", ha="left", va="center", fontsize=12)

ax.set_ylabel(r"$\varphi(x)$")

ax.set_xlim(-4, 4)
ax.set_ylim(0, max(phi) * 1.08)

ax.set_xticks([0])
ax.set_yticks([])

ax.grid(False)

path = "/home/tysser/Scripts/jetbrains/cpp_course/III_course/2025-12-26-semester-assessments/tests/gauss.png"
plt.tight_layout()

if save:
    path = "gauss.png"
    plt.savefig(path, dpi=200, bbox_inches="tight")

plt.show()

