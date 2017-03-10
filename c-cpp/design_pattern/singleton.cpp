// 类的声明放在.h文件中
class ModelManager {
public:
	// 禁用默认的copy构建与复制构建
	// 禁用默认的移动copy构建与移动复制构建
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator =(const ModelManager&) = delete;
	ModelManager(const ModelManager&&) = delete;
	ModelManager& operator =(const ModelManager&&) = delete;
	
    static ModelManager& Get();
    ~ModelManager();

    // 能够在这个类型上进行的计算
    // todo
private:
    // 构造函数放在私有声明中,防止有其它访问方法来解决类实例
    ModelManager();

private:
    // 类的其它属性
};

// 下面的内容放在实现文件.cpp中
ModelManager& ModelManager::Get()
{
    static ModelManager mm;
    return mm;
}