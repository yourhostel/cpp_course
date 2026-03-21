# Щільність стандартного нормального розподілу

$$\varphi(x)=\frac{1}{\sqrt{2\pi}}e^{-x^2/2}$$

$N (0, 1)$:
```cpp
double laplace_local_phi(const double x)
{
    return (1.0 / std::sqrt(2.0 * std::numbers::pi_v<double>)) * std::exp(-x * x / 2.0);
}
```

З параметрами $a$ і $\sigma$, $N (a, \sigma^2)$:

$$f(x)=\frac{1}{\sigma\sqrt{2\pi}}\exp\left(-\frac{(x-a)^2}{2\sigma^2}\right)$$

Запис через стандартну щільність:

$$f(x)=\frac{1}{\sigma}\varphi\left(\frac{x-a}{\sigma}\right)$$

```cpp
double normal_density(double x, double a, double sigma)
{
    return (1.0 / sigma) * laplace_local_phi((x - a) / sigma);
}
```

