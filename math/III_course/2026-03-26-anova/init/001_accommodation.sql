-- 001_accommodation.sql

create table if not exists hostel_stays
(
    id bigserial primary key,

    hostel text not null,
    room text,
    last_name text,
    full_name text,

    source_file_date date,
    checkin_date date not null,
    checkout_date date not null,

    prise integer,
    tariff_term integer,
    stay_days integer not null,

    total_price numeric(12,2) not null,
    revenue_per_day numeric(12,2) not null,

    source text
    );

create index if not exists idx_hostel_stays_hostel
    on hostel_stays(hostel);

create index if not exists idx_hostel_stays_stay_days
    on hostel_stays(stay_days);

create index if not exists idx_hostel_stays_tariff_term
    on hostel_stays(tariff_term);