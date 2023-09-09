semsan_ty_ftype semsan_fd_get_type(int fd) {
  struct kstat stat;
  int err = vfs_fstat(fd, &stat);

  if (err)
    return (semsan_ty_ftype)semsan_inval;
  // TODO: are they using the same macros?
  else if (S_ISREG(stat.mode))
    return semsan_FT_REG;
  else if (S_ISDIR(stat.mode))
    return semsan_FT_DIR;
  else if (S_ISCHR(stat.mode))
    return semsan_FT_CHR;
  else if (S_ISBLK(stat.mode))
    return semsan_FT_BLK;
  else if (S_ISFIFO(stat.mode))
    return semsan_FT_FIFO;
  else if (S_ISLNK(stat.mode))
    return semsan_FT_LNK;
  else if (S_ISSOCK(stat.mode))
    return semsan_FT_SOCK;
  else
    return (semsan_ty_ftype)semsan_inval;
}

bool semsan_fd_get_is_open(int fd) {
  struct fd f = fdget_pos(fd);
  return f.file;
}

unsigned int semsan_fd_get_flags(int fd) {
  struct fd f = fdget_pos(fd);
  if (!f.file)
    return (unsigned int)semsan_inval;
  return f.file.f_flags;
}

size_t semsan_fd_get_off(int fd) {
  struct fd f = fdget_pos(fd);
  if (!f.file)
    return (unsigned int)semsan_inval;
  return f.file->f_pos;
}

size_t semsan_fd_get_len(int fd) {
  // TODO: len?
}
