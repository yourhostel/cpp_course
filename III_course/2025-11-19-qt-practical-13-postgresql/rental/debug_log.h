//
// Created by tysser on 21.11.25.
//

// III_course/2025-11-19-qt-practical-13-postgresql/rental/debug_log.h
#ifndef CPP_COURSE_DEBUG_LOG_H
#define CPP_COURSE_DEBUG_LOG_H

// 0 = вимкнено
// 1 = увімкнено
#define ENABLE_DEBUG 0

#if ENABLE_DEBUG
    #include <QDebug>
    #define DLOG(...) qDebug() << __VA_ARGS__
#else
    #define DLOG(...) do {} while(0)
#endif

#endif //CPP_COURSE_DEBUG_LOG_H