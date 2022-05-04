#include "sort_merge_join.h"
#include <assert.h>
#include <algorithm> 

st_table SortMergeJoin::join(const st_table& t1, const st_table& t2, const int join_idx) {
    assert (t1.size() > join_idx && t2.size() > join_idx);

    //sort data
    st_table sorted_t1 = sort_table(t1, join_idx);
    st_table sorted_t2 = sort_table(t2, join_idx);

    // merge
    st_table merged_t = merge_table(sorted_t1, sorted_t2, join_idx);


    return merged_t;
}

st_table SortMergeJoin::sort_table(const st_table& t, const int join_idx) {
    class Compare {
    public:
        Compare(int key_id) : m_key_id(key_id) {}
        ~Compare() {}

        bool operator() (st_row_data row1, st_row_data row2) {
            return (row1[m_key_id] < row2[m_key_id]);
        }

    private:
        const int m_key_id;
    };

    st_table tmp = t;

    std::sort(tmp.begin(), tmp.end(), Compare(join_idx));

    return tmp;
}


st_table SortMergeJoin::merge_table(const st_table& t1, const st_table& t2, const int join_idx) {
    auto t1_itr = t1.begin();
    auto t2_itr = t2.begin();

    st_table output_tab;

    for (; t1_itr != t1.end() && t2_itr != t2.end(); ) {
        auto& row1 = *t1_itr;
        auto& row2 = *t2_itr;

        if (row1[join_idx] < row2[join_idx]) {
            t1_itr ++;
        } 
        else if (row1[join_idx] == row2[join_idx])
        {
            st_row_data tmp = *t1_itr;
            tmp.insert(tmp.end(), t2_itr->begin(), t2_itr->end());
            output_tab.push_back(tmp);

            t1_itr ++;
            t2_itr ++;
        }
        else
        {
            t2_itr ++;
        }
    }

    return output_tab;
}
