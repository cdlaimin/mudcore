/**
 * @brief CURL接口
 *
 */

nosave mapping fd_msg;

// 客户端响应，请重写此接口处理响应
protected void response(string result)
{
    debug(result);
}

protected void on_read(int fd, string msg)
{
    // debug_message(sprintf("on_read: %d msg: %s", fd, msg));
    fd_msg[fd] += sprintf("%s", msg);
}

protected void on_write(int fd)
{
    debug_message(sprintf("on_write: %d", fd));
}

protected void on_close(int fd)
{
    // debug_message(sprintf("on_close: %d", fd));
    socket_close(fd);
    response(fd_msg[fd]);
    map_delete(fd_msg, fd);
}

object curl(string arg)
{
#if efun_defined(external_start)
    int fd;
    int CURL_CMD = 1;
    if (__ARCH__ == "Microsoft Windows")
        CURL_CMD = 2;

    if (!arg)
        arg = "";
    fd = external_start(CURL_CMD, arg, "on_read", "on_write", "on_close");

    if (!fd_msg)
    {
        fd_msg = ([]);
    }
    fd_msg[fd] = "";
#else
    debug("不支持 external_start");
#endif
    return this_object();
}