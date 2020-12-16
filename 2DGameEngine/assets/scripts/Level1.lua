local currentSystemHour = os.date("*t").hour
local mapTextureAssetId = "terrain-texture-day"

if currentSystemHour > 9 and currentSystemHour < 18 then
    mapTextureAssetId = "terrain-texture-day"
else
    mapTextureAssetId = "terrain-texture-night"
end

Level1 = {
    assets = {
        [0] = { type="texture", id = "terrain-texture-day", file = "./assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "terrain-texture-night", file = "./assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "chopper-texture", file = "./assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "tank-texture-riger-right", file = "./assets/images/tank-tiger-right.png" },
        [4] = { type="texture", id = "projectile-texture", file = "./assets/images/bullet.png" },
        [5] = { type="texture", id = "heliport-texture", file = "./assets/images/base-landing.png"},
        [6] = { type="texture", id = "radar-texture", file = "./assets/images/radar-spritesheet.png"},
        [7] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", fontSize = 14 }
    },

    map = {
        textureAssetId = mapTextureAssetId,
        file = "./assets/tilemaps/jungle.map",
        scale = 2,
        tileSize = 32,
        mapSizeX = 25,
        mapSizeY = 20
    },
    entities = {
        [0] = {
            name = "player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 240,
                        y = 106
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1
                },
                sprite = {
                    textureAssetId = "chopper-texture",
                    animated = true,
                    frameCount = 2,
                    animationSpeed = 90,
                    hasDirection = true,
                    fixed = false
                },
                collider = {
                    tag = "player",
                    draw = true
                },
                input = {
                    keyboard = {
                        up = "w",
                        left = "a",
                        down = "s",
                        right = "d",
                        shoot = "space",
                        box = "c"
                    }
                }
            }
        },

        [1] = {
            name = "tank-enemy-1",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 150,
                        y = 500
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1
                },
                sprite = {
                    textureAssetId = "tank-texture-riger-right",
                    animated = false
                },
                collider = {
                    tag = "tank",
                    draw = false
                },
                projectileEmitter = {
                    textureAssetId = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 50,
                    range = 200,
                    angle = 0,
                    shouldLoop = true,
                    scale = 1
                }
            }  
        },

        [2] = {
            name = "heliport",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 450,
                        y = 400
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },
                    width = 64,
                    height = 64,
                    scale = 1,
                },

                sprite = {
                    textureAssetId = "heliport-texture",
                    animated = false;
                },
                collider = {
                    tag = "flag",
                    draw = false
                }
            }
        },

        [3] = 
        {
            name = "radar",
            layer = 6,
            components = 
            {
                transform = 
                {
                    position = 
                    {
                        x = 720,
                        y = 15
                    },
                    velocity = 
                    {
                        x = 0,
                        y = 0
                    },

                    width = 64,
                    height = 64,
                    scale = 1,
                },

                sprite = 
                {
                    textureAssetId = "radar-texture",
                    animated = true,
                    frameCount = 8,
                    animationSpeed = 150,
                    hasDirection = false,
                    fixed = true
                }
            }
        }
    }
}