package com.my.game.UserInterface;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;

public class UiHearts {

    private Texture texture;
    private int healthCount;

    public UiHearts(Texture texture){
        this.texture = texture;

    }

    public void update(float dt, int playerHealth){
        healthCount = playerHealth;
    }

    public void render(SpriteBatch batch, Vector2 cameraPos){

        for (int i = 0; i < healthCount / 10; i++) {
            batch.draw(texture, cameraPos.x + i * 30 - 300, cameraPos.y - 225, 16, 16);

        }
    }

    public void dispose(){
        texture.dispose();
    }
}
