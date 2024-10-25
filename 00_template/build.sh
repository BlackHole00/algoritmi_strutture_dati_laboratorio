cc="clang"
args="-std=c99"
src_dir="src"
build_dir="build"

# Building
for source in `find $src_dir -name *.c`; do
	$cc -c $source -o $build_dir/${source//\//_}.o $args || exit 1
done

# Linking
link_files=""
for object in `find $build_dir -name *.o`; do
	link_files+=" $object"
done

$cc $link_files -o $build_dir/main $args || exit 1

# Cleanup
rm $build_dir/*.o

 
