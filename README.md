# README
## Run
```bash
mkdir build && cd build
cmake ..
make -j
python ../test.py
```

## Hard Link and Symbol Link
### 文件的创建过程
- data写入硬盘
- 创建一个reference，叫做inode，指向data的起始地址
- filename被创建，指向inode
### 创建hard link
- 创建一个新的filename也指向这个inode
- 因此修改其中一个，会导致另一个的修改
- 删掉源文件，新的那个还在
- 只能指向文件
### 创建symbol link
- 可以指向文件或文件夹
- 指向文件
  - 两者同步
  - 删除symbol link，源文件还在
  - 删除源文件，symbol link还在但是失效
- 指向文件夹
  - 想要删除symbol link，需要`rm dir`
  - 想要删除symbol link里面的内容，需要`rm dir/`