/**
 * 目录分隔符
 */
declare const __ds = ''

/**
 * 当前脚本绝对路径
 */
declare const __filename = ''

/**
 * 当前脚本的绝对目录
 */
declare const __dirname = ''

/**
 * 指针对象
 */
declare class pointer { }

/**
 * Buffer数据对象
 */
declare class Buffer { }

/**
 * 一个类似点的对象，只要满足有 {x,y}两个属性就可以
 */
declare class PointLike {
    x: Number
    y: Number
}

/**
 * 一个类似尺寸的对象，只要满足有 {w,h}两个属性就可以
 */
declare class SizeLike {
    w: Number
    h: Number
}

/**
 * 一个类似矩形的对象，只要满足有 {x,y,w,h}两个属性就可以
 */
declare class RectLike extends PointLike, SizeLike { }

/**
 * 图像匹配结果的对象，是一个 RectLike 对象，同时有一个score分数，是匹配的得分，0-1之间 
 */
declare class TplMatchResult extends RectLike {
    score: Number
}

/**
 * 获取绝对路径，根据cwd来计算
 * @param path 路径
 */
declare function realpath(path: String): String

/**
 * 获取目录路径
 * @param path 路径
 */
declare function dirname(path: String): String

/**
 * 获取运行程序目录
 */
declare function entry_path(): String

/**
 * 获取指定文件模式的文件列表
 * @param pattern 目录模式
 */
declare function glob(pattern: String): Array<String>

/**
 * 获取当前工作路径
 */
declare function cwd(): String

/**
 * 等待
 * @param microtimes 毫秒
 */
declare function sleep(microtimes: Number)

/**
 * 结束
 * @param code 错误码 ,默认值0
 */
declare function exit(code: Number = 0)

// 窗口相关方法
/**
 * 鼠标获取窗口句柄
 */
declare function win_from_mouse(): Number

/**
 * 查看窗口位置 {x,y}
 * @param hwnd 窗口句柄
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_position(hwnd: Number, clientOnly: Boolean = true): Object

/**
 * 设置窗口位置
 * @param hwnd 窗口句柄
 * @param pointLike 一个点坐标{x,y}
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_set_position(hwnd: Number, pointLike: Object, clientOnly: Boolean = true)

/**
 * 设置窗口大小
 * @param hwnd 窗口句柄
 * @param sizeLike 一个尺寸对象{w,h}
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_resize(hwnd: Number, sizeLike: Object, clientOnly: Boolean = true)

/**
 * 窗口区域 {x,y,w,h}
 * @param hwnd 窗口句柄
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_rect(hwnd: Number, clientOnly: Boolean = true): Object

/**
 * 窗口大小{w,h}
 * @param hwnd 窗口句柄
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_size(hwnd: Number, clientOnly: Boolean = true): Object

/**
 * 截图,返回图像指针
 * @param hwnd 窗口句柄
 * @param rectLike 截图矩形区域
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_capture(hwnd: Number, rectLike: Object, clientOnly: Boolean = true): pointer

/**
 * 窗口截图,返回图像指针
 * @param hwnd 窗口句柄
 * @param clientOnly 客户窗口区域,默认true
 */
declare function win_capture(hwnd: Number, clientOnly: Boolean = true): pointer

/**
 * 窗口激活
 * @param hwnd 窗口句柄
 */
declare function win_active(hwnd: Number)

/**
 * 设置窗口层叠关系
 * @param hwnd 窗口句柄
 * @param insertAfter 在哪个窗口句柄之后,也可以是 0=HWND_TOP  1=HWND_BOTTOM  -1=HWND_TOPMOST  -2=HWND_NOTOPMOST
 */
declare function win_zorder(hwnd: Number, insertAfter: Number)

/**
 * 设置窗口显示属性
 * @param hwnd 窗口句柄
 * @param showCmd 窗口显示属性 SW_*
 */
declare function win_show(hwnd: Number, showCmd: Number)

// 鼠标相关方法
/**
 * 鼠标滚动
 * @param hwnd 窗口句柄
 * @param pointLike 窗口坐标点(以clientOnly区域) {x,y}
 * @param step 滚动距离, 负数向下滚,正数向上滚,默认鼠标滚动一格是120步长
 */
declare function mouse_scroll(hwnd: Number, pointLike: Object, step: Number = -120)

/**
 * 
 * @param hwnd 窗口句柄
 * @param pointLike 坐标点
 * @param btn 按键 -1左键(默认),0滚轮键,1右键
 */
declare function mouse_click(hwnd: Number, pointLike: Object, btn: Number = -1)

/**
 * 双击
 * @param hwnd 窗口句柄
 * @param pointLike 坐标点
 * @param btn 按键(默认-1)
 */
declare function mouse_dbclick(hwnd: Number, pointLike: Object, btn: Number = -1)

/**
 * 移动
 * @param hwnd 窗口句柄
 * @param pointLike 坐标点
 * @param btn 按键(默认-1)
 */
declare function mouse_move(hwnd: Number, pointLike: Object, btn: Number = -1)

/**
 * 按键抬起
 * @param hwnd 窗口句柄
 * @param pointLike 坐标点
 * @param btn 按键(默认-1)
 */
declare function mouse_up(hwnd: Number, pointLike: Object, btn: Number = -1)

/**
 * 按键按下
 * @param hwnd 窗口句柄
 * @param pointLike 坐标点
 * @param btn 按键(默认-1)
 */
declare function mouse_down(hwnd: Number, pointLike: Object, btn: Number = -1)

// 图像相关方法
/**
 * 图像销毁,请不要重复调用该函数,调用一次就可以了
 * @param p 图像句柄
 */
declare function mat_release(p: pointer)

/**
 * 截取区域
 * @param p 图像句柄
 * @param rectLike 矩形区域
 */
declare function mat_crop(p: pointer, rectLike: Object)

/**
 * 模板查找 返回 Array<{x,y,score,w,h}>
 * @param p 原始图像
 * @param tpl 模板图像
 * @param rectLikes 在这些区域内查找
 */
declare function mat_find(p: pointer, tpl: pointer, ...rectLikes: Array<Object>): Array<Object>

/**
 * 图像预览
 * @param p 图像句柄
 * @param title 显示标题 默认 "mat-show"
 */
declare function mat_show(p: pointer, title: String = 'mat - show')

/**
 * 等待按键,返回按键码 ,返回-1是超时
 * @param timeout 等待按键延迟,单位ms,0=一直等待(默认)
 */
declare function wait_key(timeout: Number = 0): Number

/**
 * 创建图像
 * @param data 图片数据
 * @param fmt 格式化,binary二进制,base64 (默认)
 */
declare function mat_make(data: String | Buffer, fmt: String = 'base64'): pointer

/**
 * 根据图片路径返回图像
 * @param path 图片路径,默认这个是以当前工作路径为相对路径,而不是以当前脚本路径
 */
declare function mat_read(path: String): pointer
