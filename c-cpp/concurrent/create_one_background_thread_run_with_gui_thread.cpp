#include <thread>
#include <future>

std::atomic<bool> thread_finished(false);

//下面是后台线程的入口函数原型
return_type func_name(param_type1, param_type2);

//创建一个future的管理对象
std::packaged_task<return_type(param_type1, param_type2)>(func_name);
//或者下面的形式也可以
std::packaged_task<return_type(param_type1, param_type2)>([](param_type1 p1, param_type2 p2){});

std::future<return_type> thread_return_result = task.get_future();

//生成工作线程
std::thread worker(std::move(task), true_p1, true_p2);

//在主UI线程中循环检查后台线程是否已经返回
//注意:work_finished是一个全局的原子性的变量
//要在后台线程中对它进行修改, 后台函数的每一个出口处将其置位
while (!work_finished.load())
{
	//修改图形界面, 刷新图形界面, 暂时一定的时间
	
}

//主线程等待子线程的结束
worker.join();

return_type result = thread_return_result.get()

//使用return_type_result进行后续处理
//...