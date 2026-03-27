--------------------------------------
-- Таблиця для нормалізованих даних --
--------------------------------------

CREATE TABLE IF NOT EXISTS hostel_stays
(
    id BIGSERIAL PRIMARY KEY,

    hostel TEXT NOT NULL,
    room TEXT,
    last_name TEXT,
    full_name TEXT,

    source_file_date DATE,
    checkin_date DATE NOT NULL,
    checkout_date DATE NOT NULL,

    prise INTEGER,
    tariff_term INTEGER,
    stay_days INTEGER NOT NULL,

    total_price NUMERIC(12,2) NOT NULL,
    revenue_per_day NUMERIC(12,2) NOT NULL,

    source TEXT
);