#pragma once

struct GroupStats
{
    int group_id;
    long long group_size;
    double group_mean;
    double within_group_variance;
    double min_value;
    double max_value;
    double median;
    double p25;
    double p75;
};