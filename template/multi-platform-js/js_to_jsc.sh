#!/bin/bash
SRC_PATH=""
JSB_EXEC="../../tools/plugin_jscompile/bin/jsbcc"

function getdir(){
    
    for element in `ls $1`
      do
        dir_or_file=$1"/"$element
    if [ -d $dir_or_file ]
      then
        getdir $dir_or_file
      else
        FILE_ARRAY=(${dir_or_file[*]}  ${FILE_ARRAY[*]})   
    fi
done
}

FILE_ARRAY=()
function help(){
    echo "
    USAGE EXAMPLE: ./js_to_jsc -s srcpath -d dstpath
    HELP
    "
    exit 0
}
rm -rf ./release
if [ ! -d "./release" ]; then
  mkdir ./release
  cp -r ./Resources ./release/Resources
  SRC_PATH="./release/Resources"
fi

getdir $SRC_PATH
for item in ${FILE_ARRAY[*]}
  do
    SRC_FILE=$item
    SRC=${SRC_PATH#*/}
    if [ "${item##*.}"x = "js"x ];then
      # echo $item
      EXEC_STR=${item/$SRC/$SRC}
      EXEC_STR=${EXEC_STR%.*}
      CMD="$JSB_EXEC $SRC_FILE "$EXEC_STR".cross"
      
      $CMD
      rm -rf $item
    fi
  done

zip -r ./release/Resources.zip ./release/Resources


# # -d dst  -s src -h help
# while getopts "d:s:h" opt
# do
#     case $opt in
#         d)
#         DST_PATH=$OPTARG
#         ;;
#         s)
#         SRC_PATH=$OPTARG
#         ;;
#         h)
#         help
#         exit 0
#         ;;
#         ?)
#         help
#         exit 0
#         ;;
#         *)
#         help
#         exit 0
#         ;;
#     esac
# done

# if [ x"$SRC_PATH" = x ]; 
#     then 
#         help
#         exit 1
# fi

# if [ x"$DST_PATH" = x ]; 
#     then 
#         help
#         exit 1
# fi







