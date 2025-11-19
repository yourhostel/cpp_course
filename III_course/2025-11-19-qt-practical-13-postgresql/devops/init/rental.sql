-- Видаляємо старі таблиці, якщо вони існують
DROP TABLE IF EXISTS rentals CASCADE;
DROP TABLE IF EXISTS customers CASCADE;
DROP TABLE IF EXISTS tapes CASCADE;

---------------------------------------------------
-- Таблиця 1 — Касети
---------------------------------------------------
CREATE TABLE tapes (
                       tape_id SERIAL PRIMARY KEY,              -- Код касети
                       title VARCHAR(25) NOT NULL,              -- Назва касети
                       type VARCHAR(35) NOT NULL,               -- Тип касети
                       price NUMERIC(10,2) NOT NULL,            -- Ціна прокату за добу
                       description TEXT                          -- Опис вмісту (MEMO)
);

---------------------------------------------------
-- Таблиця 2 — Клієнти
---------------------------------------------------
CREATE TABLE customers (
                           customer_id SERIAL PRIMARY KEY,           -- Код клієнта
                           full_name VARCHAR(30) NOT NULL,           -- ПІБ
                           info TEXT                                 -- Додаткова інформація (паспорт, адреса)
);

---------------------------------------------------
-- Таблиця 3 — Пункт прокату (операції)
---------------------------------------------------
CREATE TABLE rentals (
                         rental_id SERIAL PRIMARY KEY,             -- Код операції
                         tape_id INTEGER NOT NULL,                 -- Код касети (зовнішній ключ)
                         issue_date DATE NOT NULL,                 -- Дата видачі
                         return_date DATE,                         -- Дата прийому
                         customer_id INTEGER NOT NULL,             -- Код клієнта (зовнішній ключ)
                         copies INTEGER NOT NULL DEFAULT 1,        -- Кількість копій
                         deadline DATE,                            -- Термін повернення
                         returned BOOLEAN DEFAULT FALSE,           -- Ознака повернення

    -- Зовнішні ключі (звʼязки 1-to-many)
    -- Клієнти (один до багатьох) Пункт прокату (багато до одного) Касети
                         FOREIGN KEY (tape_id) REFERENCES tapes(tape_id),
                         FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);
