docker run -it \
    --net=host \
    -v /home/honnen/Desktop/binocular-recon-rgb:/workspace/binocular-recon-rgb \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -e DISPLAY=unix$DISPLAY \
    -e GDK_SCALE \
    -e GDK_DPI_SCALE \
    --gpus all \
    --name binocular-recon-rgb thecanadianroot/opencv-cuda:ubuntu20.04-cuda11.3.1-opencv4.5.2