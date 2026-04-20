# Повторення незалежних випробувань.

Формула Бернуллі. Формула Муавра–Лапласа. Формула Пуассона

## Порівняльна характеристика

| Характеристика              | Бернуллі                                            | Локальна теорема Лапласа                                     | Інтегральна теорема Лапласа                                             | Пуассона                                                         |
|-|-|-|-|-|
| Основна формула             | $P_n(m)=C_n^m p^m q^{n-m}$                          | $P_n(m)\approx \frac{1}{\sqrt{npq}}\varphi(x)$               | $P_n(m_1\le X\le m_2)\approx \Phi(x_2)-\Phi(x_1)$$                      | $P_n(m)\approx \frac{\lambda^m e^{-\lambda}}{m!}$                |
| Аргумент стандартизації     | не потрібен                                         | $x=\frac{m-np}{\sqrt{npq}}$                                  | $x_1=\frac{m_1-np}{\sqrt{npq}},\quad x_2=\frac{m_2-np}{\sqrt{npq}}$     | $\lambda=np$                                                     |
| Тип моделі                  | точна біноміальна                                   | наближена біноміальна                                        | наближена біноміальна                                                   | наближення біноміального розподілу                               |
| Тип змінної                 | дискретна                                           | дискретна, але наближається неперервною нормальною моделлю   | дискретна, але сумарна ймовірність обчислюється через нормальний розподіл | дискретна                                                        |
| Що обчислює                 | ймовірність точно $m$ успіхів у $n$ випробуваннях   | ймовірність точно $m$ успіхів при великих $n$                | ймовірність потрапляння числа успіхів у проміжок                        | ймовірність точно $m$ рідкісних подій                            |
| Типова подія                | рівно $m$                                           | рівно $m$                                                    | не менше, не більше, від $m_1$ до $m_2$                                 | рівно $m$, інколи також суми ймовірностей                        |
| Умови застосування          | незалежні випробування, стала ймовірність успіху $p$ | $n$ велике, $p$ не надто близьке до 0 або 1, зазвичай $npq>9$ | $n$ велике, $p$ не надто близьке до 0 або 1, зазвичай $npq>9$           | $n$ велике, $p$ мале, $np=\lambda$ скінченне, зазвичай $p\le 0.1$ |
| Основний параметр           | $n,p,q,m$                                           | $n,p,q,m,x$                                                  | $n,p,q,m_1,m_2,x_1,x_2$                                                 | $\lambda=np,\ m$                                                 |
| Тип задач                   | малі або помірні $n$, точний рахунок                | великі $n$, треба одна точка                                 | великі $n$, треба інтервал                                              | рідкісні події, мала ймовірність успіху                          |
| Перевага                    | точний результат                                    | швидке наближення                                            | зручно для нерівностей і проміжків                                      | дуже зручно для малих $p$                                        |
| Недолік                     | громіздко при великих $n$                           | лише наближення                                              | лише наближення, потрібна таблична функція                              | працює не для всіх $p$                                           |
| Коли обирати в першу чергу  | коли $n$ невелике                                   | коли питають рівно одне значення при великому $n$            | коли питають менше, більше, від і до                                    | коли подія рідкісна                                              |
| Приклад формулювання задачі | із 10 паперів подорожчає рівно 5                    | із 300 виробів буде рівно 250 першосортних                   | із 100 клієнтів менше 15 замовлять квиток                               | із 2000 абонентів за годину зателефонують 5                      |

де:

## Таблиця параметрів

|  № |   Позначення |                  Зміст                   |   № |             Позначення |                    Зміст                     |
|-:|-------------:|:----------------------------------------:|-:|-----------------------:|:--------------------------------------------:|
|  1 |          $n$ |     кількість незалежних випробувань     |   9 |              $\lambda$ |  параметр розподілу Пуассона, $\lambda=np$   |
|  2 |          $p$ | ймовірність успіху в одному випробуванні |  10 |                   $np$ |    математичне сподівання $\mathbb{E}[X]$    |
|  3 |          $q$ |      ймовірність неуспіху, $q=1-p$       |  11 |                  $npq$ |          дисперсія $\mathbb{D}[X]$           |
|  4 |          $m$ |            кількість успіхів             |  12 |    $\sigma=\sqrt{npq}$ |        середньоквадратичне відхилення        |
|  5 |          $X$ |    випадкова величина, число успіхів     |  13 |                   $$x$ |         нормований аргумент Лапласа          |
|  6 |      $C_n^m$ | число комбінацій, $$\frac{n!}{m!(n-m)!}$ |  14 |           $\varphi(x)$ | щільність стандартного нормального розподілу |
|  7 |     $P(X=m)$ |      ймовірність рівно $m$ успіхів       |  15 |              $\Phi(x)$ |               функція Лапласа                |
|  8 |   $Bin(n,p)$ |          біноміальний розподіл           |  16 |               $F_0(x)$ |    стандартна нормальна функція розподілу    |

## Таблиця вибору метода

| Ознака задачі                                                   | Що брати                   |
|-|-|
| Потрібна точна ймовірність, $n$ невелике                        | Бернуллі                   |
| Потрібно знайти ймовірність рівно одного значення, $n$ велике   | Локальна теорема Лапласа   |
| Потрібно знайти ймовірність проміжку, типу не менше, не більше, від і до | Інтегральна теорема Лапласа |
| $p$ дуже мале, а $n$ велике                                     | Пуассона                   |

<div style="width:1140px; margin:0; padding:0;">
<table style="border-collapse:collapse; table-layout:fixed; width:1140px; text-align:center; font-family:'Times New Roman', serif; color:#111; font-size:18px;">
  <colgroup>
    <col style="width:13.2%;">
    <col style="width:22.5%;">
    <col style="width:16.3%;">
    <col style="width:14.7%;">
    <col style="width:17.7%;">
    <col style="width:15.6%;">
  </colgroup>
  <tr>
    <th colspan="4" style="border:1px solid #222; background:#c9d6c2; padding:8px 6px; font-weight:normal; font-size:22px; color:#111;">
      Порядок слідування враховується
    </th>
    <th colspan="2" style="border:1px solid #222; background:#e2bcbc; padding:8px 6px; font-weight:normal; font-size:22px; color:#111;">
      Порядок слідування не враховується
    </th>
  </tr>
  <tr>
    <th colspan="2" style="border:1px solid #222; background:#b7c6d6; padding:10px 6px; color:#111;">
      <div style="font-weight:bold; font-size:24px; line-height:1.15;">Перестановка</div>
      <div style="font-style:italic; font-size:20px; line-height:1.15;">(P фр., permutation)*</div>
    </th>
    <th colspan="2" style="border:1px solid #222; background:#c6d3d6; padding:10px 6px; color:#111;">
      <div style="font-weight:bold; font-size:24px; line-height:1.15;">Розміщення</div>
      <div style="font-style:italic; font-size:20px; line-height:1.15;">(A фр., arrangement)</div>
    </th>
    <th colspan="2" style="border:1px solid #222; background:#d9d9d9; padding:10px 6px; color:#111;">
      <div style="font-weight:bold; font-size:24px; line-height:1.15;">Комбінація</div>
      <div style="font-style:italic; font-size:20px; line-height:1.15;">(C лат., <span style="text-decoration:underline wavy #c62828;">combinatio</span>)</div>
    </th>
  </tr>
  <tr>
    <td style="border:1px solid #222; background:#b7c6d6; padding:14px 8px; vertical-align:middle; height:180px; color:#111;">
      <div style="font-style:italic; font-size:26px; line-height:1.2;">
        P<sub>n</sub> = n!
      </div>
    </td>
    <td style="border:1px solid #222; background:#b7c6d6; padding:14px 8px; vertical-align:middle; height:180px; color:#111;">
      <div style="font-style:italic; font-size:25px; line-height:1.2;">
        P&#x0303;<sub>n</sub> =
        <span style="display:inline-block; vertical-align:middle;">
          <span style="display:block; border-bottom:1px solid #111; padding:0 3px;">n!</span>
          <span style="display:block; padding-top:2px;">k<sub>1</sub>!k<sub>2</sub>!...k<sub>m</sub>!</span>
        </span>
      </div>
      <div style="font-style:italic; font-size:23px; line-height:1.2; margin-top:10px;">
        k<sub>1</sub> + k<sub>2</sub> + ... + k<sub>m</sub> = n
      </div>
      <div style="font-style:italic; font-size:24px; line-height:1.2; margin-top:10px;">
        P&#x0303; =
        <span style="display:inline-block; vertical-align:middle;">
          <span style="display:block; border-bottom:1px solid #111; padding:0 3px;">n!</span>
          <span style="display:block; padding-top:2px;">∏ k(a)!</span>
        </span>
      </div>
      <div style="font-style:italic; font-size:20px; line-height:1;">a</div>
    </td>
    <td style="border:1px solid #222; background:#c6d3d6; padding:14px 8px; vertical-align:middle; height:180px; color:#111;">
      <div style="font-style:italic; font-size:26px; line-height:1.2;">
        A<sub>n</sub><sup>k</sup> =
        <span style="display:inline-block; vertical-align:middle;">
          <span style="display:block; border-bottom:1px solid #111; padding:0 3px;">n!</span>
          <span style="display:block; padding-top:2px;">(n - k)!</span>
        </span>
      </div>
    </td>
    <td style="border:1px solid #222; background:#c6d3d6; padding:14px 8px; vertical-align:middle; height:180px; color:#111;">
      <div style="font-style:italic; font-size:26px; line-height:1.2;">
        A&#x0303;<sub>n</sub><sup>k</sup> = n<sup>k</sup>
      </div>
      <div style="font-size:20px; line-height:1.25; margin-top:10px;">декартов добуток</div>
      <div style="font-size:20px; line-height:1.25; margin-top:10px;">Ω × Ω × ... × Ω</div>
      <div style="font-size:20px; line-height:1.25; margin-top:10px;"><span style="font-style:italic; font-size:24px;">k</span> разів</div>
    </td>
    <td style="border:1px solid #222; background:#d9d9d9; padding:14px 8px; vertical-align:middle; height:180px; color:#111;">
      <div style="font-style:italic; font-size:26px; line-height:1.2;">
        C<sub>n</sub><sup>k</sup> =
        <span style="display:inline-block; vertical-align:middle;">
          <span style="display:block; border-bottom:1px solid #111; padding:0 3px;">n!</span>
          <span style="display:block; padding-top:2px;">k!(n - k)!</span>
        </span>
      </div>
    </td>
    <td style="border:1px solid #222; background:#d9d9d9; padding:14px 8px; vertical-align:middle; height:180px; color:#111;">
      <div style="font-style:italic; font-size:26px; line-height:1.2;">
        C&#x0303;<sub>n</sub><sup>k</sup> = C<sub>n+k-1</sub><sup>k</sup>
      </div>
    </td>
  </tr>

  <tr>
    <td style="border:1px solid #222; background:#b7c6d6; padding:8px 6px; font-style:italic; font-size:20px; color:#111;">Без повторень</td>
    <td style="border:1px solid #222; background:#b7c6d6; padding:8px 6px; font-style:italic; font-size:20px; color:#111;">З повтореннями</td>
    <td style="border:1px solid #222; background:#c6d3d6; padding:8px 6px; font-style:italic; font-size:20px; color:#111;">Без повторень</td>
    <td style="border:1px solid #222; background:#c6d3d6; padding:8px 6px; font-style:italic; font-size:20px; color:#111;">З повтореннями</td>
    <td style="border:1px solid #222; background:#d9d9d9; padding:8px 6px; font-style:italic; font-size:20px; color:#111;">Без повторень</td>
    <td style="border:1px solid #222; background:#d9d9d9; padding:8px 6px; font-style:italic; font-size:20px; color:#111;">З повтореннями</td>
  </tr>

  <tr>
    <td colspan="2" style="border:1px solid #222; background:#c9d6c2; padding:8px 6px; font-size:20px; color:#111;">
      Всі елементи входять до сполуки
    </td>
    <td colspan="4" style="border:1px solid #222; background:#e2bcbc; padding:8px 6px; font-size:20px; color:#111;">
      Не всі елементи входять до сполуки
    </td>
  </tr>
</table>
</div>

---

```bash
pandoc README.md -s \
  --pdf-engine=xelatex \
  --columns=60 \
  -V mainfont="DejaVu Serif" \
  -V monofont="DejaVu Sans Mono" \
  -V fontsize=12pt \
  -V linestretch=1.15 \
  -V geometry:a4paper \
  -V geometry:margin=20mm \
  -V geometry:landscape \
  --toc --toc-depth=3 \
  --number-sections \
  --metadata title="Теорія ймовірностей та математична статистика" \
  --metadata subtitle="Повторення незалежних випробувань. Формули: Бернуллі, Муавра–Лапласа, Пуассона" \
  --metadata author="Тищенко Сергій, alk-43" \
  --metadata date="2026-04-20" \
  -H ../../../header.tex \
  -o README.pdf
```