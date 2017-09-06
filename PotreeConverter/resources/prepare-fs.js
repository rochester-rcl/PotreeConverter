Module['mountNODEFS'] = function(virtualRoot) {
  FS.mkdir(virtualRoot);
  FS.mount(NODEFS, { root: '.' }, virtualRoot);
};

Module['mountWORKERFS'] = function(virtualRoot, file) {
  FS.mkdir(virtualRoot);
  FS.mkdir('/archive');
  FS.mount(WORKERFS, {
    files: [file],
  }, virtualRoot );
};

Module['ls'] = function(path) {
  return FS.readdir(path);
}

Module['lookup'] = function(path) {
  return FS.lookupPath(path);
}

Module['onRuntimeInitialized'] = function() {
  return true;
}
