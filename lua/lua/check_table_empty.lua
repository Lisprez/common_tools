-- 检查lua中的一个表是否为空
function IsTableEmpty(tableName)
	local next_ = next
	if next_(tableName) == nil then
		return true
	else
		return false
	end
end

-- 获取lua中一个表中有多少个元素, 当是第一级的元素
function GetTableSize(tableName)
	local size = 0
	for _ in pairs(table) do
		size = size + 1
	end

	return size
end