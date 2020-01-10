declare const Duktape = {
    version: 0, // 版本号
    env: '', // 环境
    fin(obj: Object, finalizer?: Function): void | Function { }, // 设置或者获取finalizer
    enc(format: String, data: String | Buffer): String { }, // 编码 hex base64 jx jc
    dec(format: String, data: String | Buffer): String { }, // 解码 hex base64 jx jc
    info(): Object { }, // Get internal information (such as heap address and alloc size) of a value in a version specific format. The C API equivalent is duk_inspect_value().
    act() { }, // Get information about call stack entry.
    gc() { }, // 垃圾回收
    compact(obj: Object): Object { }, // Compact the memory allocated for a value (object)
    errCreate(err) { },    // Callback to modify/replace a created error.
    errThrow(err) { }, // 
    Pointer(p: pointer | any) { }, // Pointer constructor
    Thread(f: Function) { }, // Thread constructor
}
