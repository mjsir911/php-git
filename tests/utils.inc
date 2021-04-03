<?php
define("TEST_REPO", "tests/repo.git");
// from zip's test suite
/* recursively remove a directory */
function rmdir_rf($dir) {
    if ($handle = opendir($dir)) {
        while (false !== ($item = readdir($handle))) {
            if ($item != "." && $item != "..") {
                if (is_dir($dir . '/' . $item)) {
                    rmdir_rf($dir . '/' . $item);
                } else {
                    unlink($dir . '/' . $item);
                }
            }
        }
        closedir($handle);
        rmdir($dir);
    }
}

// https://stackoverflow.com/a/20340043
const DS = DIRECTORY_SEPARATOR; // for convenience

function getRelativePath($from, $to) {
    $dir = explode(DS, is_file($from) ? dirname($from) : rtrim($from, DS));
    $file = explode(DS, $to);

    while ($dir && $file && ($dir[0] == $file[0])) {
        array_shift($dir);
        array_shift($file);
    }
    return str_repeat('..'.DS, count($dir)) . implode(DS, $file);
}

function localRepo($dir) {
	return exec("git clone --quiet tests/repo.git {$dir}");
}
?>
