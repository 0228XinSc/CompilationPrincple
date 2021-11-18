### DeBug

1. 语法分析中将else 无大括号 跟的IF（）中的if（）当作函数调用

   修改语法分析中的Unary 加特判ident 不能是 if



<img src="C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20211027010222434.png" alt="image-20211027010222434" style="zoom:50%;" />

<img src="C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20211027012248798.png" alt="image-20211027012248798" style="zoom:50%;" />

2.<img src="C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20211027181641049.png" alt="image-20211027181641049" style="zoom:50%;" />

未定义名字出问题，重定位位置有问题。定位在func，while，if， else

重定位直接在block尾部。

tle 因为判断函数类型是直接在FuncRParams中return了，导致语法分析无法正常结束。

3.<img src="C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20211027190559640.png" alt="image-20211027190559640" style="zoom:50%;" />

d有问题

注意函数在没有形参时，给形参个数置零

m有问题，没有考虑while嵌套的情况。

```
while(){
	while(){
		
	}
	break;//此时会输出m错误
}
{
	break;
	continue;
}
/*不是在Block就置*/
```

c 输出行号为变量位置的行号CurPos-1；

b名字重定义问题。

单独一个{}重定位问题

函数调用时，参数是void函数问题。