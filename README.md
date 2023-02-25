# 词典程序

## 构建

1. 进入`dictionary/`文件夹
2. 运行`make dictionary`
3. 运行成功后，会在`dictionary/`目录下生成`dictionary.exe`

## 命令

```txt
insert	<中文>  <英文>	  // 插入一个条目：<中文> 对应 <英文>
delete  <中文>           // 删除 <中文> 所对应的条目
update  <中文>  <现英文>  // 更新 <中文> 所对应的条目：<中文> 对应 <现英文>
search  <中文>           // 查找 <中文> 所对应的条目
translate  <英文>        // 查找 <英文> 所对应的中文（第一次出现）
load    <文件名>         // 导入文件 
save    <文件名>         // 将词典保存到文件里
help                    // 获取命令帮助
exit                    // 退出程序
```

## 演示

```txt
command > insert 中文 Chinese
Insert Complete
command > insert 英语 English
Insert Complete
command > search 中文
Search Result: Chinese
command > translate English
Translate Result: 英语
command > insert 英文 English
Insert Complete
command > translate English
Translate Result: 英语
command > delete 英语
Delete Complete
command > translate English
Translate Result: 英文
command > save testDatas
Save Complete
command > exit

// 第二次打开
command > load testDatas.data
Load Complete
command > search 中文
Search Result: Chinese
command > search 英文
Search Result: English
command > search 英语
Not Found!
command > translate English
Translate Result: 英文
command > translate Chinese
Translate Result: 中文
command > exit
```

## 教程

[使用说明](https://www.bilibili.com/video/BV1U84y177TF/?share_source=copy_web&vd_source=ab26e7710bc0979e20c08f2417d84cf8)

