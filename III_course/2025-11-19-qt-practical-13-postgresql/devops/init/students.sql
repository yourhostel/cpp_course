-- Видаляємо таблицю, якщо вона вже існує (для DataGrip, щоб можна було запускати багато разів)
DROP TABLE IF EXISTS students CASCADE;

---------------------------------------------------
-- Таблиця студентів групи
---------------------------------------------------
CREATE TABLE students (
                          id SERIAL PRIMARY KEY,           -- Унікальний ідентифікатор студента
                          last_name TEXT NOT NULL,         -- Прізвище
                          first_name TEXT NOT NULL,        -- Ім'я
                          middle_name TEXT,                -- По батькові (необов’язкове)
                          birth_date DATE,                 -- Дата народження
                          photo_path TEXT                  -- Шлях до файлу фотографії (зберігається у ФС)
);