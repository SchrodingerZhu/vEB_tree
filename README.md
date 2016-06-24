# vEB_tree
The giant data structure of van Emde Boas tree.

<p>（1）在此Git中，vEB树的版本有两种，num_vEB和normal_vEB(现标记为vEB_unfinished),num_vEB相当于具有vEB结构的有序正整数集;而暂且没有完工的normal_vEB则是使用模板的范型数据结构。</p>
<p>（2）对于normal_vEB，计划使用pair<long long,T>储存数据，即first值为KEY，second值为具体数据</p>
<p>（3）对于两种vEB都有的属性为：<br/>
        空间占用	               O(M)  <br/>
        方法member(key)	           O(log log M)  //返回bool，看键值为key的元素是否存在<br/>
        方法insert(key)	           O(log log M)  //void，插入键值为key的元素，对于normal_vEB：insert(key,T)<br/>
        方法erase(key)	           O(log log M)  //void，删除键值为key的元素<br/>
        方法successor(key)         O(log log M)  //long long，返回后一个元素的键值<br/>
        方法predecessor(key)       O(log log M)  //long long，返回前一个元素的键值<br/>
        对于normal_vEB，还有一个专有方法，get_value(key)，由于返回键值为key的元素的second值。     
</p>
    
  
