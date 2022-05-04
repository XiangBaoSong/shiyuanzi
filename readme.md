## 源码简介

```shell
.
├── dynamic_hash                    ##### 动态hash算法实现 #####
│   ├── data_def.h                  # 通用数据结构定义
│   ├── dynamic_hash.cpp            # 动态hash实现
│   ├── dynamic_hash.h              # 动态hash头文件
│   ├── hash_algorithm_factory.h 	# hash算法实例化工厂方法
│   ├── hash_algorithm.h 			# hash实例接口类
│   ├── int_hash.cpp                # 整数hash算法具体实现
│   ├── int_hash.h                  # 整数hash算法头文件
│   ├── string_hash.cpp 			# 字符串hash算法实现
│   ├── string_hash.h               # 字符串hash算法头文件
│   └── test.cpp                    # 动态hash测试代码
├── merge_algorithm					#####join 3种算法实现 #####
│   ├── data_def.h					# 通过数据结构定义
│   ├── hash_join.cpp				# hash join算法实现
│   ├── hash_join.h					# hash join算法头文件
│   ├── join_method_factory.h		# join算法工厂方法
│   ├── join_method.h          		# join算法 接口类
│   ├── nested_loop_join.cpp		# 嵌套循环join算法实现
│   ├── nested_loop_join.h			# 嵌套循环算法实现
│   ├── sort_merge_join.cpp			# 排序合并join算法实现
│   ├── sort_merge_join.h			# 排序合并join算法头文件
│   └── test.cpp					# join算法测试代码
```

## 资料参考情况

- postgress 动态hash算法源码

> 程序流程图：https://www.processon.com/view/link/6262a4b6e401fd79f6f00db8
>
> 源码地址：https://github.com/postgres/postgres/blob/master/src/backend/utils/hash/dynahash.c
>
> backend---->util---->util---->hash---danyhash.c

- mysql innoDB double write源码

> 源码地址：[ttps://github.com/mysql/mysql-server/tree/8.0/storage](https://github.com/mysql/mysql-server/tree/8.0/storage)
>
> storage---->innobase---->buf0dblwr.cc
>
> 程序流程图`https://www.processon.com/view/link/62729621079129397f3319d3`
>
> 类与对象图：`https://www.processon.com/view/link/627296981efad45d06d8d40c`

- 三种join算法原理

> 三种join算法原理：https://cloud.tencent.com/developer/article/1572210
>
> nested loop merge:[ttps://zhuanlan.zhihu.com/p/81398139](https://zhuanlan.zhihu.com/p/81398139)



## 总结

- 在posttgress源码和mysql double write源码阅读上花费时间最多，累计8小时；而在代码实现上累计只有6小时；
- 后面为了完成任务，动态hash直接使用了网上的源码，然后进行C++版本的改造，没有仔细阅读每一个细节；