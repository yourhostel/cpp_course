-----------------------------
-- Функція критерій Фішера --
-----------------------------

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

----------------------------------
-- функція для зведеної таблиці --
----------------------------------

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