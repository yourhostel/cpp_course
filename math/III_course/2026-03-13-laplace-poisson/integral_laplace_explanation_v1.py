import numpy as np
import matplotlib.pyplot as plt

n = 100
p = 0.4
q = 1 - p
k1 = 35
k2 = 50

mu = n * p
sigma = np.sqrt(n * p * q)
x1 = (k1 - mu) / sigma
x2 = (k2 - mu) / sigma

x = np.linspace(-4, 4, 1000)
phi = (1 / np.sqrt(2 * np.pi)) * np.exp(-x**2 / 2)

fig, ax = plt.subplots(figsize=(10, 6))
ax.plot(x, phi, linewidth=2)
ax.fill_between(x, phi, where=(x >= x1) & (x <= x2), alpha=0.3)
ax.axvline(x1, linewidth=1.5)
ax.axvline(x2, linewidth=1.5)

# labels moved vertically to center
ax.text(x1, max(phi) * 0.5, rf"$x_1 \approx {x1:.2f}$", ha="right", va="center", fontsize=12)
ax.text(x2, max(phi) * 0.5, rf"$x_2 \approx {x2:.2f}$", ha="left", va="center", fontsize=12)

formula_text = (
    rf"$P(k_1 \leq X \leq k_2) \approx \Phi(x_2)-\Phi(x_1)$" "\n"
    rf"$x_1=\dfrac{{k_1-np}}{{\sqrt{{npq}}}},\quad x_2=\dfrac{{k_2-np}}{{\sqrt{{npq}}}}$" "\n"
    rf"$n={n},\ p={p},\ q={q},\ k_1={k1},\ k_2={k2}$" "\n"
    rf"$np={mu:.0f},\ \sqrt{{npq}} \approx {sigma:.2f}$"
)

ax.text(
    0.02, 0.98, formula_text,
    transform=ax.transAxes,
    va="top",
    ha="left",
    fontsize=12,
    bbox=dict(boxstyle="round", alpha=0.15)
)

ax.set_title("Інтегральна теорема Лапласа")
ax.set_xlabel("Нормована координата x")
ax.set_ylabel(r"$\varphi(x)$")
ax.set_xlim(-4, 4)
ax.set_ylim(0, max(phi) * 1.08)
ax.grid(True, alpha=0.25)

out_path = "math/III_course/2026-03-13-laplace-poisson/integral_laplace_explanation_v1.png"
plt.tight_layout()
plt.savefig(out_path, dpi=200, bbox_inches="tight")
plt.show()

print(out_path)
