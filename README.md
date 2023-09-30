# Text-relevance-comparison
数据结构课程综合项目——使用C语言实现基于词频的文本相关性比较  
Term Project of Data Structures and Programming -  Using C language to realize word frequency based text relevance comparison
  
 1.    首先分别统计所提供的两个文本文件中单词出现频率（即出现次数）。
为了提高算法的准确性，在此只统计字典中出现且不为停用词（stop-word）的单词。单词为仅由字母组成的字符序列，包含大写字母的单词将大写字母转换为小写字母后进行词频统计。提供字典“dictionary.txt”文件和英文停用词表“stopwords.txt”文件。  
  
 2.    分别取两个文本文件中出现频率最高的前N个单词（按单词出现频率进行排序，频率相同的单词按字典序，然后取前N个单词。若单词数不足N，则按实际数目）。假设两个文本文件中出现频率最高的前N个单词中有M个单词相同，分别计算这M个单词在两个文本的前N个单词中的频率占比：  
 
![image](https://user-images.githubusercontent.com/95207487/157656980-ea6c93f5-662e-4874-b21c-cb7a13d3018e.png)  


   其中Freq’i为两个文本文件中词频最高的前N个单词中共有的M个单词中每个单词在某一文本中出现的频率；Freqj为某一文本中前N个词频最高的单词的频率（若不足N，则按实际数目）。  
    
3.    最后计算两个文本的相关度。假设Pro1和Pro2分别为两个文本文件中词频最高的前N个单词中共有词的频率占比，则两个文本文件的相关度计算公式为：  
![image](https://user-images.githubusercontent.com/95207487/157657144-47a5e4f2-41c5-4df2-ad3e-dd99173cc18e.png)  

输入：整数N
输出：相似度Sim  

排序算法为插入排序，查找算法为顺序查找，进一步优化可提高性能
  
