int dup(int oldfd) {
    return fcntl(oldfd, F_DUPFD, STDERR_FILENO);
}

int dup2(int oldfd, int newfd) {

    if(oldfd == newfd)
        return oldfd;

    if(fcntl(oldfd, F_GETFD) == -1)
        return -1;

    if(close(newfd) == -1 && errno != EBADF)
        return -1;

    fcntl(oldfd, F_DUPFD, newfd);

    return newfd;
}
