#include "../include/parse.h"

char *read_file_into_str(const char *str)
{
    int fd;
    char *line;
    char *temp;
    char *file_content;

    fd = open(str, O_RDONLY);
    if (fd == -1)
        error_exit("Error open filen\n");
    file_content = ft_strdup("");
    line = get_next_line(fd);
    
    while (line != NULL)
    {
        temp = ft_strjoin(file_content, line);
        free(file_content);
        free(line);
        file_content = temp;
        line = get_next_line(fd);
        printf("line: %s\n", line);
    }
    write(1, "suuu", 4);

    return (file_content);
}

t_scene parse(char **str) {
    char **ptr;
    int i;
    t_scene scene;
    scene.objects.head = NULL;
    i = 0;
    while (str[i]) 
    {
        ptr = ft_split(str[i], ' ');
        if (!strncmp(ptr[0], "A", ft_strlen(ptr[0])))
            parse_ambient_lightning(ptr, &scene.amb_light);
        else if (!strncmp(ptr[0], "C", ft_strlen(ptr[0])))
            parse_camera(ptr, &scene.camera);
        else if (!strncmp(ptr[0], "L", ft_strlen(ptr[0])))
            parse_light(ptr, &scene.spot_light);
        else
            parse_object(ptr, &scene.objects);
        free_split(ptr);
        i++;
    }
    return (scene);
}


t_scene check_and_fill(char **argv)
{
    t_scene scene;
    
    char *str = read_file_into_str(argv[1]);
    char **ptr = ft_split(str, '\n');
    scene = parse(ptr);
    free(str);
    int i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
    return (scene);
}
