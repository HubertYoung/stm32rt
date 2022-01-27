
#include "test.h"



/**
 * @brief     ssd1306 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t ssd1306(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            ssd1306_info_t info;
            
            /* print ssd1306 info */
            ssd1306_info(&info);
            ssd1306_interface_debug_print("ssd1306: chip is %s.\n", info.chip_name);
            ssd1306_interface_debug_print("ssd1306: manufacturer is %s.\n", info.manufacturer_name);
            ssd1306_interface_debug_print("ssd1306: interface is %s.\n", info.interface);
            ssd1306_interface_debug_print("ssd1306: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            ssd1306_interface_debug_print("ssd1306: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            ssd1306_interface_debug_print("ssd1306: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            ssd1306_interface_debug_print("ssd1306: max current is %0.2fmA.\n", info.max_current_ma);
            ssd1306_interface_debug_print("ssd1306: max temperature is %0.1fC.\n", info.temperature_max);
            ssd1306_interface_debug_print("ssd1306: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            ssd1306_interface_debug_print("ssd1306: SPI interface SCK connected to GPIOA PIN5.\n");
            ssd1306_interface_debug_print("ssd1306: SPI interface MISO connected to GPIOA PIN6.\n");
            ssd1306_interface_debug_print("ssd1306: SPI interface MOSI connected to GPIOA PIN7.\n");
            ssd1306_interface_debug_print("ssd1306: SPI interface CS connected to GPIOA PIN4.\n");
            ssd1306_interface_debug_print("ssd1306: SPI interface cmd data gpio GPIO connected to GPIOA PIN8.\n");
            ssd1306_interface_debug_print("ssd1306: SPI interface reset GPIO connected to GPIOB PIN0.\n");
            ssd1306_interface_debug_print("ssd1306: IIC interface SCL connected to GPIOB PIN8.\n");
            ssd1306_interface_debug_print("ssd1306: IIC interface SDA connected to GPIOB PIN9.\n");
            ssd1306_interface_debug_print("ssd1306: IIC interface reset GPIO connected to GPIOB PIN0.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show ssd1306 help */
            
            help:
            
            ssd1306_interface_debug_print("ssd1306 -i\n\tshow ssd1306 chip and driver information.\n");
            ssd1306_interface_debug_print("ssd1306 -h\n\tshow ssd1306 help.\n");
            ssd1306_interface_debug_print("ssd1306 -p\n\tshow ssd1306 pin connections of the current board.\n");
            ssd1306_interface_debug_print("ssd1306 -t display -spi\n\trun ssd1306 display test by spi interface.\n");
            ssd1306_interface_debug_print("ssd1306 -t display -iic -a (0 | 1)\n\trun ssd1306 display test by iic interface."
                                          "0 or 1 means the iic address pin level.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -spi -init\n\trun ssd1306 init by spi interface.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -iic -a (0 | 1)\n\trun ssd1306 init by iic interface."
                                          "0 or 1 means the iic address pin level.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -deinit\n\trun ssd1306 deinit function.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -str <string>\n\trun ssd1306 show string function.string is the shown string.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -displayon\n\trun ssd1306 display on function.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -displayoff\n\trun ssd1306 display off function.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -clear\n\trun ssd1306 clear screen function.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -writepoint <x> <y> <data>\n\trun ssd1306 writepoint function.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -readpoint <x> <y>\n\trun ssd1306 readpoint function.\n");
            ssd1306_interface_debug_print("ssd1306 -c basic -rect <x1> <y1> <x2> <y2>\n\trun ssd1306 drawing rectangle function."
                                          "x1 means x start.y1 means y start.x2 means x end.y2 means y end.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -spi -init\n\trun ssd1306 init by spi interface.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -iic -a (0 | 1)\n\trun ssd1306 init by iic interface."
                                          "0 or 1 means the iic address pin level.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -deinit\n\trun ssd1306 deinit function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -str <string>\n\trun ssd1306 show string function.string is the shown string.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -displayon\n\trun ssd1306 display on function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -displayoff\n\trun ssd1306 display off function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -clear\n\trun ssd1306 clear screen function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -writepoint <x> <y> <data>\n\trun ssd1306 writepoint function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -readpoint <x> <y>\n\trun ssd1306 readpoint function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -rect <x1> <y1> <x2> <y2>\n\trun ssd1306 drawing rectangle function."
                                          "x1 means x start.y1 means y start.x2 means x end.y2 means y end.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -enable_zoom\n\trun ssd1306 enable zoom function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -disable_zoom\n\trun ssd1306 disable zoom function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -deactivate_scroll\n\trun ssd1306 deactivate scroll function.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -fade_blinking (disable | fade_out | blinking) <frame>\n\t"
                                          "run ssd1306 fade blinking function.frames means the running frames.\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -vertical_left_horizontal_scroll <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 "
                                          "| FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256)\n\t");
            ssd1306_interface_debug_print("run ssd1306 setting vertical left horizontal scroll function.startpage means start page and"
                                          "it can be \"0\"-\"7\".endpage means end page and it can be \"0\"-\"7\".rows means display rows"
                                          "and it can be \"0\" - \"63\".\n");
            ssd1306_interface_debug_print("ssd1306 -c advance -vertical_right_horizontal_scroll <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 "
                                          "| FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256)\n\t");
            ssd1306_interface_debug_print("run ssd1306 setting vertical right horizontal scroll function.startpage means start page and"
                                          "it can be \"0\"-\"7\".endpage means end page and it can be \"0\"-\"7\".rows means display rows"
                                          "and it can be \"0\" - \"63\".\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* display test */
            if (strcmp("display", argv[2]) == 0)
            {
                /* check spi */
                if (strcmp("-spi", argv[3]) != 0)
                {
                    return 5;
                }
                /* run reg test */
                if (ssd1306_display_test(SSD1306_INTERFACE_SPI, SSD1306_ADDR_SA0_0))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run functions */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                volatile uint8_t res;

                if (strcmp("-displayon", argv[3]) == 0)
                {
                    res = ssd1306_basic_display_on();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: display on failed.\n");
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: display on.\n");
                    
                    return 0;
                }
                else if (strcmp("-displayoff", argv[3]) == 0)
                {
                    res = ssd1306_basic_display_off();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: display off failed.\n");
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: display off.\n");
                    
                    return 0;
                }
                else if (strcmp("-clear", argv[3]) == 0)
                {
                    res = ssd1306_basic_clear();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: clear screen.\n");
                    
                    return 0;
                }
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    res = ssd1306_basic_deinit();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: deinit failed.\n");
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: deinit ssd1306.\n");
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                volatile uint8_t res;

                if (strcmp("-displayon", argv[3]) == 0)
                {
                    res = ssd1306_advance_display_on();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: display on failed.\n");
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: display on.\n");
                    
                    return 0;
                }
                else if (strcmp("-displayoff", argv[3]) == 0)
                {
                    res = ssd1306_advance_display_off();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: display off failed.\n");
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: display off.\n");
                    
                    return 0;
                }
                else if (strcmp("-clear", argv[3]) == 0)
                {
                    res = ssd1306_advance_clear();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: clear screen.\n");
                    
                    return 0;
                }
                else if (strcmp("-deinit", argv[3]) == 0)
                {
                    res = ssd1306_advance_deinit();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: deinit failed.\n");
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: deinit ssd1306.\n");
                    
                    return 0;
                }
                else if (strcmp("-enable_zoom", argv[3]) == 0)
                {
                    res = ssd1306_advance_enable_zoom_in();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: enable zoom in failed.\n");
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: enable zoom in.\n");
                    
                    return 0;
                }
                else if (strcmp("-disable_zoom", argv[3]) == 0)
                {
                    res = ssd1306_advance_disable_zoom_in();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: disable zoom in failed.\n");
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: disable zoom in.\n");
                    
                    return 0;
                }
                else if (strcmp("-deactivate_scroll", argv[3]) == 0)
                {
                    res = ssd1306_advance_deactivate_scroll();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: deactivate scroll failed.\n");
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: deactivate scroll.\n");
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                volatile uint8_t res;
                
                if (strcmp("-str", argv[3]) == 0)
                {
                    res = ssd1306_basic_clear();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    res = ssd1306_basic_string(0, 0, argv[4], strlen(argv[4]), 1, SSD1306_FONT_16);
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: show string failed.\n");
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: %s.\n", argv[4]);
                    
                    return 0;
                }
                else if (strcmp("-spi", argv[3]) == 0)
                {
                    if (strcmp("-init", argv[4]) == 0)
                    {
                        volatile uint8_t res;
                        
                        res = ssd1306_basic_init(SSD1306_INTERFACE_SPI, SSD1306_ADDR_SA0_0);
                        if (res)
                        {
                            ssd1306_basic_deinit();
                            
                            return 1;
                        }
                        ssd1306_interface_debug_print("ssd1306: ssd1306: init success.\n");
                        
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                volatile uint8_t res;
                
                if (strcmp("-str", argv[3]) == 0)
                {
                    res = ssd1306_advance_clear();
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    res = ssd1306_advance_string(0, 0, argv[4], strlen(argv[4]), 1, SSD1306_FONT_16);
                    if (res)
                    {
                        ssd1306_interface_debug_print("ssd1306: show string failed.\n");
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: %s.\n", argv[4]);
                    
                    return 0;
                }
                else if (strcmp("-spi", argv[3]) == 0)
                {
                    if (strcmp("-init", argv[4]) == 0)
                    {
                        volatile uint8_t res;
                        
                        res = ssd1306_advance_init(SSD1306_INTERFACE_SPI, SSD1306_ADDR_SA0_0);
                        if (res)
                        {
                            ssd1306_advance_deinit();
                            
                            return 1;
                        }
                        ssd1306_interface_debug_print("ssd1306: ssd1306: init success.\n");
                        
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* display test */
            if (strcmp("display", argv[2]) == 0)
            {
                ssd1306_address_t addr;
                
                /* check iic */
                if (strcmp("-iic", argv[3]) != 0)
                {
                    return 5;
                }
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr = SSD1306_ADDR_SA0_0;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr = SSD1306_ADDR_SA0_1;
                }
                else
                {
                    return 5;
                }
                /* run reg test */
                if (ssd1306_display_test(SSD1306_INTERFACE_IIC, addr))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run functions */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                if (strcmp("-readpoint", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    volatile uint8_t data;
                    
                    res = ssd1306_basic_read_point(atoi(argv[4]), atoi(argv[5]), (uint8_t *)&data);
                    if (res)
                    {
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: read point %d %d is %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)data);
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                if (strcmp("-readpoint", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    volatile uint8_t data;
                    
                    res = ssd1306_advance_read_point(atoi(argv[4]), atoi(argv[5]), (uint8_t *)&data);
                    if (res)
                    {
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: read point %d %d is %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)data);
                    
                    return 0;
                }
                else if (strcmp("-fade_blinking", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    const char str[4][16]= {"disable", "", "fade out", "blinking"};
                    ssd1306_fade_blinking_mode_t mode;
                    
                    if (strcmp("disable", argv[4]) == 0)
                    {
                        mode = SSD1306_FADE_BLINKING_MODE_DISABLE;
                    }
                    else if (strcmp("fade_out", argv[4]) == 0)
                    {
                        mode = SSD1306_FADE_BLINKING_MODE_FADE_OUT;
                    }
                    else if (strcmp("blinking", argv[4]) == 0)
                    {
                        mode = SSD1306_FADE_BLINKING_MODE_BLINKING;
                    }
                    else
                    {
                        return 5;
                    }
                    res = ssd1306_advance_fade_blinking(mode, atoi(argv[5]));
                    if (res)
                    {
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: set fade blinking %s mode with %d frames.\n", str[mode], (uint8_t)(atoi(argv[5])));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                volatile uint8_t res;
                ssd1306_address_t addr;
                
                /* check iic */
                if (strcmp("-iic", argv[3]) == 0)
                {
                    /* check iic address */
                    if (strcmp("-a", argv[4]) != 0)
                    {
                        return 5;
                    }
                    if (strcmp("0", argv[5]) == 0)
                    {
                        addr = SSD1306_ADDR_SA0_0;
                    }
                    else if (strcmp("1", argv[5]) == 0)
                    {
                        addr = SSD1306_ADDR_SA0_1;
                    }
                    else
                    {
                        return 5;
                    }
                    /* check init */
                    if (strcmp("-init", argv[6]) == 0)
                    {
                        res = ssd1306_basic_init(SSD1306_INTERFACE_IIC, addr);
                        if (res)
                        {
                            ssd1306_basic_deinit();
                            
                            return 1;
                        }
                        ssd1306_interface_debug_print("ssd1306: init success.\n");
                        
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else if (strcmp("-writepoint", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = ssd1306_basic_write_point(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
                    if (res)
                    {
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: write point %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance test */
            else if (strcmp("advance", argv[2]) == 0)
            {
                volatile uint8_t res;
                ssd1306_address_t addr;
                
                /* check iic */
                if (strcmp("-iic", argv[3]) == 0)
                {
                    /* check iic address */
                    if (strcmp("-a", argv[4]) != 0)
                    {
                        return 5;
                    }
                    if (strcmp("0", argv[5]) == 0)
                    {
                        addr = SSD1306_ADDR_SA0_0;
                    }
                    else if (strcmp("1", argv[5]) == 0)
                    {
                        addr = SSD1306_ADDR_SA0_1;
                    }
                    else
                    {
                        return 5;
                    }
                    /* check init */
                    if (strcmp("-init", argv[6]) == 0)
                    {
                        res = ssd1306_advance_init(SSD1306_INTERFACE_IIC, addr);
                        if (res)
                        {
                            ssd1306_advance_deinit();
                            
                            return 1;
                        }
                        ssd1306_interface_debug_print("ssd1306: init success.\n");
                        
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else if (strcmp("-writepoint", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = ssd1306_advance_write_point(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
                    if (res)
                    {
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: write point %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        /* run functions */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic test */
            if (strcmp("basic", argv[2]) == 0)
            {
                if (strcmp("-rect", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = ssd1306_basic_rect(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), 1);
                    if (res)
                    {
                        ssd1306_basic_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: draw rect %d %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint8_t)atoi(argv[7]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* advance fucntion */
            else if (strcmp("advance", argv[2]) == 0)
            {
                if (strcmp("-rect", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    
                    res = ssd1306_advance_rect(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), 1);
                    if (res)
                    {
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: draw rect %d %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]), (uint8_t)atoi(argv[7]));
                    
                    return 0;
                }
                else if (strcmp("-vertical_left_horizontal_scroll", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    ssd1306_scroll_frame_t frames;
                    
                    if (strcmp("FRAME_2", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_2;
                    }
                    else if (strcmp("FRAME_3", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_3;
                    }
                    else if (strcmp("FRAME_4", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_4;
                    }
                    else if (strcmp("FRAME_5", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_5;
                    }
                    else if (strcmp("FRAME_25", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_25;
                    }
                    else if (strcmp("FRAME_64", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_64;
                    }
                    else if (strcmp("FRAME_128", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_128;
                    }
                    else if (strcmp("FRAME_256", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_256;
                    }
                    else
                    {
                        return 5;
                    }
                    res = ssd1306_advance_vertical_left_horizontal_scroll(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), frames);
                    if (res)
                    {
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: vertical left horizontal scroll start stop rows frames %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]));
                    
                    return 0;
                }
                else if (strcmp("-vertical_right_horizontal_scroll", argv[3]) == 0)
                {
                    volatile uint8_t res;
                    ssd1306_scroll_frame_t frames;
                    
                    if (strcmp("FRAME_2", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_2;
                    }
                    else if (strcmp("FRAME_3", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_3;
                    }
                    else if (strcmp("FRAME_4", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_4;
                    }
                    else if (strcmp("FRAME_5", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_5;
                    }
                    else if (strcmp("FRAME_25", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_25;
                    }
                    else if (strcmp("FRAME_64", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_64;
                    }
                    else if (strcmp("FRAME_128", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_128;
                    }
                    else if (strcmp("FRAME_256", argv[7]) == 0)
                    {
                        frames = SSD1306_SCROLL_FRAME_256;
                    }
                    else
                    {
                        return 5;
                    }
                    res = ssd1306_advance_vertical_right_horizontal_scroll(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), frames);
                    if (res)
                    {
                        ssd1306_advance_deinit();
                        
                        return 1;
                    }
                    ssd1306_interface_debug_print("ssd1306: vertical right horizontal scroll start stop rows frames %d %d %d.\n", (uint8_t)atoi(argv[4]), (uint8_t)atoi(argv[5]), (uint8_t)atoi(argv[6]));
                    
                    return 0;
                }
                else
                {
                    return 5;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}
