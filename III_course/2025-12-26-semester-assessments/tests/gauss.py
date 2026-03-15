import sys
import numpy as np
import matplotlib.pyplot as plt

save = "-p" in sys.argv

x = np.linspace(-4, 4, 1000)
phi = (1 / np.sqrt(2 * np.pi)) * np.exp(-x**2 / 2)

plt.figure(figsize=(8,5))

plt.plot(x, phi, linewidth=2)
plt.fill_between(x, phi, color="#a6c8ff")

# x-axis
plt.axhline(0, linewidth=1.5)

# vertical line at maximum
plt.axvline(0, linewidth=1.5)

plt.text(
    0.02, 0.98,
    r"$\varphi(x)=\frac{1}{\sqrt{2\pi}}e^{-x^2/2}$",
    transform=plt.gca().transAxes,
    va="top",
    ha="left",
    fontsize=12,
    bbox=dict(
        boxstyle="round",
        facecolor="#e6f2ff",
        edgecolor="gray",
        alpha=1
    )
)

plt.text(
    0.5, 0.5,
    r"$\int_{-\infty}^{\infty}\varphi(x)\,dx=1$",
    transform=plt.gca().transAxes,
    va="center",
    ha="center",
    fontsize=12,
    bbox=dict(
        boxstyle="round",
        facecolor="#e6f2ff",
        edgecolor="gray",
        alpha=1
    )
)

# only show 0 on x-axis
plt.xticks([0], ["0"],fontsize=14)
plt.yticks([])

# position infinity labels slightly above the curve near the edges
y_pos = phi.max() * 0.01
plt.text(-3.9, y_pos, r"$-\infty$", ha="left", va="bottom", fontsize=20)
plt.text(3.9, y_pos, r"$+\infty$", ha="right", va="bottom", fontsize=20)

plt.xlim(-4,4)
plt.ylim(0, phi.max()*1.1)

path = "/home/tysser/Scripts/jetbrains/cpp_course/III_course/2025-12-26-semester-assessments/tests/gauss.png"
plt.tight_layout()

if save:
    path = "gauss.png"
    plt.savefig(path, dpi=200, bbox_inches="tight")

plt.show()
