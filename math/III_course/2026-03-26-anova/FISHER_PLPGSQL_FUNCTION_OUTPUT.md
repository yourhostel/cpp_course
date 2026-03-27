```SQL
SELECT*
FROM hostel_stays
WHERE revenue_per_day > 500;

-- Загальна кількість в групах
SELECT stay_days, count(*)
FROM hostel_stays
GROUP BY stay_days
ORDER BY stay_days;

-- Контроль підготовки даних:
SELECT
    id,
    checkin_date,
    checkout_date,
    stay_days,
    prise
FROM hostel_stays
WHERE stay_days IN (1, 7, 28)
LIMIT 10;

-- дохід по групах
SELECT
    stay_days AS група,
    COUNT(*) AS кількість,
    SUM(total_price) AS сума_ціни
FROM hostel_stays
WHERE stay_days IN (1, 7, 28)
GROUP BY stay_days
ORDER BY stay_days;

-- формування вибірок як окремих груп
-- Група 1 (ціна за день)
SELECT revenue_per_day
FROM hostel_stays
WHERE stay_days = 1
LIMIT 10;

-- Група 2 (ціна за тиждень)
SELECT revenue_per_day
FROM hostel_stays
WHERE stay_days = 7
LIMIT 10;

-- Група 3
SELECT revenue_per_day
FROM hostel_stays
WHERE stay_days = 28
LIMIT 10;

-- Загальне середнє bar{х}
WITH filtered_data AS (
    SELECT
        revenue_per_day
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
)
SELECT
    AVG(revenue_per_day) AS загальне_середнє
FROM filtered_data;

-- Зведена таблиця значущіх даних
SELECT
    stay_days AS "група",
    COUNT(*) AS "кількість_в_групі",
    AVG(revenue_per_day) AS "середнє_по_групі",
    VARIANCE(revenue_per_day) AS "дисперсія_всередині_групи",
    MIN(revenue_per_day) AS "мінімум",
    MAX(revenue_per_day) AS "максимум",
    PERCENTILE_CONT(0.5) WITHIN GROUP (ORDER BY revenue_per_day) AS "медіана",
    PERCENTILE_CONT(0.25) WITHIN GROUP (ORDER BY revenue_per_day) AS "p25",
    PERCENTILE_CONT(0.75) WITHIN GROUP (ORDER BY revenue_per_day) AS "p75"
FROM hostel_stays
WHERE stay_days IN (1, 7, 28)
GROUP BY stay_days
ORDER BY stay_days;

-- Група та ціна за день
SELECT
    stay_days,
    revenue_per_day
FROM hostel_stays
WHERE stay_days IN (1, 7, 28);

-- Міжгрупова сума квадратів
WITH filtered_data AS (
    SELECT
        stay_days,
        revenue_per_day
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
),
групи AS (
    SELECT
        stay_days,
        COUNT(*) AS n_i,
        AVG(revenue_per_day) AS середнє_по_групі
    FROM filtered_data
    GROUP BY stay_days
),
загальне AS (
    SELECT
        AVG(revenue_per_day) AS загальне_середнє
    FROM filtered_data
)
SELECT
    SUM(g.n_i * POWER(g.середнє_по_групі - z.загальне_середнє, 2)) AS міжгрупова_сума_квадратів
FROM групи g
CROSS JOIN загальне z;

-- Внутрішньогрупова сума квадратів
WITH filtered_data AS (
    SELECT
        stay_days,
        revenue_per_day
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
),
групи AS (
    SELECT
        stay_days,
        AVG(revenue_per_day) AS середнє_по_групі
    FROM filtered_data
    GROUP BY stay_days
)
SELECT
    SUM(POWER(d.revenue_per_day - g.середнє_по_групі, 2)) AS внутрішньогрупова_сума_квадратів
FROM filtered_data d
JOIN групи g USING (stay_days);

-- зважена об’єднана дисперсія між групами (масштабована міжгрупова варіація)
WITH filtered_data AS (
    SELECT
        stay_days,
        revenue_per_day
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
),
групи AS (
    SELECT
        stay_days,
        COUNT(*) AS n_i,
        AVG(revenue_per_day) AS середнє_по_групі
    FROM filtered_data
    GROUP BY stay_days
),
загальне AS (
    SELECT
        AVG(revenue_per_day) AS загальне_середнє
    FROM filtered_data
),
ss_between AS (
    SELECT
        SUM(g.n_i * POWER(g.середнє_по_групі - z.загальне_середнє, 2)) AS ss_between
    FROM групи g
    CROSS JOIN загальне z
)
SELECT
    ss_between / (3 - 1) AS ms_between
FROM ss_between;

-- зважена об’єднана дисперсія всередині всіх груп (сумарна внутрішня варіація)
WITH filtered_data AS (
    SELECT
        stay_days,
        revenue_per_day
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
),
групи AS (
    SELECT
        stay_days,
        AVG(revenue_per_day) AS середнє_по_групі
    FROM filtered_data
    GROUP BY stay_days
),
ss_within AS (
    SELECT
        SUM(POWER(d.revenue_per_day - g.середнє_по_групі, 2)) AS ss_within
    FROM filtered_data d
    JOIN групи g USING (stay_days)
),
параметри AS (
    SELECT
        COUNT(*) AS обсяг_вибірки
    FROM filtered_data
)
SELECT
    s.ss_within / (p.обсяг_вибірки - 3) AS ms_within
FROM ss_within s
CROSS JOIN параметри p;

-- Критерій Фішера
WITH filtered_data AS (
    SELECT
        stay_days,
        revenue_per_day
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
),
групи AS (
    SELECT
        stay_days,
        COUNT(*) AS n_i,
        AVG(revenue_per_day) AS середнє_по_групі
    FROM filtered_data
    GROUP BY stay_days
),
загальне AS (
    SELECT
        COUNT(*) AS N,
        AVG(revenue_per_day) AS загальне_середнє
    FROM filtered_data
),
ss_between AS (
    SELECT
        SUM(g.n_i * POWER(g.середнє_по_групі - z.загальне_середнє, 2)) AS ss_between
    FROM групи g
    CROSS JOIN загальне z
),
ss_within AS (
    SELECT
        SUM(POWER(d.revenue_per_day - g.середнє_по_групі, 2)) AS ss_within
    FROM filtered_data d
    JOIN групи g USING (stay_days)
),
ступені AS (
    SELECT
        3 AS k,
        z.N,
        (3 - 1) AS df_between,
        (z.N - 3) AS df_within
    FROM загальне z
),
ms AS (
    SELECT
        sb.ss_between / s.df_between AS ms_between,
        sw.ss_within / s.df_within AS ms_within
    FROM ss_between sb
    CROSS JOIN ss_within sw
    CROSS JOIN ступені s
)
SELECT
    ms_between / ms_within AS F
FROM ms;

-- pivot таблиця
SELECT
    EXTRACT(MONTH FROM checkin_date) AS місяць,
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2018) AS "2018",
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2019) AS "2019",
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2020) AS "2020",
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2021) AS "2021",
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2022) AS "2022",
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2023) AS "2023",
    AVG(revenue_per_day) FILTER (WHERE EXTRACT(YEAR FROM checkin_date) = 2024) AS "2024"
FROM hostel_stays
WHERE stay_days IN (1, 7, 28)
GROUP BY місяць
ORDER BY місяць;

-- Функція критерій Фішера
 CREATE OR REPLACE FUNCTION calculate_fisher(
    p_date_from DATE DEFAULT NULL,
    p_date_to DATE DEFAULT NULL
)
RETURNS NUMERIC
AS
$$
DECLARE
    result NUMERIC;
BEGIN
    WITH filtered_data AS (
        SELECT
            stay_days,
            revenue_per_day
        FROM hostel_stays
        WHERE stay_days IN (1, 7, 28)
          AND (p_date_from IS NULL OR checkin_date >= p_date_from)
          AND (p_date_to IS NULL OR checkin_date <= p_date_to)
    ),
    groups AS (
        SELECT
            stay_days,
            COUNT(*) AS n_i,
            AVG(revenue_per_day) AS mean_i
        FROM filtered_data
        GROUP BY stay_days
    ),
    avg AS (
        SELECT
            COUNT(*) AS n,
            AVG(revenue_per_day) AS mean_all
        FROM filtered_data
    ),
    ss_between AS (
        SELECT
            SUM(g.n_i * POWER(g.mean_i - a.mean_all, 2)) AS val
        FROM groups g
        CROSS JOIN avg a
    ),
    ss_within AS (
        SELECT
            SUM(POWER(d.revenue_per_day - g.mean_i, 2)) AS val
        FROM filtered_data d
        JOIN groups g USING (stay_days)
    ),
    ms AS (
        SELECT
            sb.val / 2 AS ms_between,
            sw.val / (a.n - 3) AS ms_within
        FROM ss_between sb
        CROSS JOIN ss_within sw
        CROSS JOIN avg a
    )
    SELECT ms_between / ms_within
    INTO result
    FROM ms;

    RETURN result;
END;
$$
LANGUAGE plpgsql;

-- Приклад виклику
-- По всіх данних
SELECT *
FROM calculate_fisher(NULL, NULL);

-- Період
SELECT *
FROM calculate_fisher('2019-01-01', '2019-12-31');

-- З певної дати
SELECT *
FROM calculate_fisher('2020-01-01', NULL);

-- Видалення, перевантаженні видаляються окремо додаючи сигнатуру
DROP FUNCTION calculate_fisher;

-- функція для зведеної таблиці
CREATE OR REPLACE FUNCTION stats_by_group(
    p_date_from DATE DEFAULT NULL,
    p_date_to DATE DEFAULT NULL
)
RETURNS TABLE
(
    group_id INT,
    group_size BIGINT,
    group_mean NUMERIC,
    within_group_variance NUMERIC,
    min_value NUMERIC,
    max_value NUMERIC,
    median NUMERIC,
    p25 NUMERIC,
    p75 NUMERIC
)
AS
$$
BEGIN
    RETURN QUERY
    SELECT
        stay_days AS group_id,
        COUNT(*) AS group_size,
        AVG(revenue_per_day)::NUMERIC AS group_mean,
        VARIANCE(revenue_per_day)::NUMERIC AS within_group_variance,
        MIN(revenue_per_day)::NUMERIC AS min_value,
        MAX(revenue_per_day)::NUMERIC AS max_value,
        PERCENTILE_CONT(0.5) WITHIN GROUP (ORDER BY revenue_per_day)::NUMERIC AS median,
        PERCENTILE_CONT(0.25) WITHIN GROUP (ORDER BY revenue_per_day)::NUMERIC AS p25,
        PERCENTILE_CONT(0.75) WITHIN GROUP (ORDER BY revenue_per_day)::NUMERIC AS p75
    FROM hostel_stays
    WHERE stay_days IN (1, 7, 28)
      AND (p_date_from IS NULL OR checkin_date >= p_date_from)
      AND (p_date_to IS NULL OR checkin_date <= p_date_to)
    GROUP BY stay_days
    ORDER BY stay_days;
END;
$$
LANGUAGE plpgsql;

-- Виклик
SELECT *
FROM stats_by_group('2019-01-01', '2019-12-31');

DROP FUNCTION stats_by_group;
```