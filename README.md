# Mine_Sweeper_X 扫雷项目

## 概率计算算法:
### Step1:遍历所有有数字的块标记出确定的雷和确定的非雷
### Step2:如果第一步标记出了雷和非雷，则重复第一步，直至不能直接确定任何块的状态
### Step3:将现有的不确定块分为不可知和可知两部分(通过周围八格是否有数字),穷举可知雷区获得所有可能解法
### Step4:列出可知区所有可能雷数，通过排列组合计算各个可能雷数概率，再将每个解法的概率代入，计算最终概率
