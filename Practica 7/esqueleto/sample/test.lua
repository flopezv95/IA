function createImage(texture_name, char_size)
	local gfxQuad = MOAIGfxQuad2D.new()
	gfxQuad:setTexture(texture_name)
	char_size = 64
	gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
	gfxQuad:setUVRect(0, 0, 1, 1)
	return gfxQuad
end

MOAISim.openWindow("game", 1024, 768)

viewport = MOAIViewport.new()
viewport:setSize (1024, 768)
viewport:setScale (1024, -768)

layer = MOAILayer2D.new()
layer:setViewport(viewport)
MOAISim.pushRenderPass(layer)

texture_name = "dragon.png"
gfxQuad = MOAIGfxQuad2D.new()
gfxQuad:setTexture(texture_name)
char_size = 64
gfxQuad = createImage("dragon.png", char_size)
gfxQuad1 = createImage("dragon_alarm.png", char_size)
gfxQuad2 = createImage("dragon_attack.png", char_size)
gfxQuad3 = createImage("dragon_dead.png", char_size)
gfxQuadMago = createImage("mago.png", char_size)
gfxQuad:setRect(-char_size/2, -char_size/2, char_size/2, char_size/2)
gfxQuad:setUVRect(0, 0, 1, 1)
  
prop = MOAIProp2D.new()
prop:setDeck(gfxQuad)
propMago = MOAIProp2D.new()
propMago:setDeck(gfxQuadMago)

entity = Character.new()
entityMago = Character.new()

-- Add Images
entity:addImage(gfxQuad)    -- SetImage(0)  dragon.png
entity:addImage(gfxQuad1)   -- SetImage(1)  dragon_alarm.png
entity:addImage(gfxQuad2)   -- SetImage(2)  dragon_attack.png
entity:addImage(gfxQuad3)   -- SetImage(3)  dragon_dead.png
-- Add prop to be the renderable for this character
entity:setProp(prop, layer)
entityMago:setProp(propMago, layer)
-- Start the character (allow calls to OnUpdate)
entityMago:setRot(90)
entityMago:setLoc(0, 400)
entityMago:setOwnerName(0)
entityMago:start()

entity:setOwnerName(1)
entity:setLoc(0, 0)
entity:start()
entity:setRot(0)
entity:setLinearVel(20, 10)
--entity:setAngularVel(30)

-- Enable Debug Draw
debug = MOAIDrawDebug.get();
layer:setDrawDebug(debug)
-- Add this character to draw debug
MOAIDrawDebug.insertEntity(entity)

mouseX = 0
mouseY = 0

function onClick(down)
  entityMago:setLoc(mouseX, mouseY)
end

function pointerCallback(x, y)
    mouseX, mouseY = layer:wndToWorld(x, y)
end

MOAIInputMgr.device.mouseLeft:setCallback(onClick)
MOAIInputMgr.device.pointer:setCallback(pointerCallback)