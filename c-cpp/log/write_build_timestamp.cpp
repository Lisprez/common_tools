// __DATE__, __TIME__, __FILE__, __LINE__
// 这些都是在构建的时候由编译器直接展开写入的
// 所以是编译时的对象, 而非运行时对象

int main() {
	printf("server build: %s %s\n", __DATE__, __TIME__);
	
	return 0;
}