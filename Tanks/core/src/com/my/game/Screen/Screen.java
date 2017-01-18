package com.my.game.Screen;

import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;

import com.my.game.MyGame;
import com.my.game.ResourceStorage.ResourceManager;

public abstract class Screen implements com.badlogic.gdx.Screen {

    public Viewport viewport;

    protected Vector2 SCREEN_SIZE;
    protected OrthographicCamera camera;
    protected Vector3 mousePosition;
    protected GameScreenManager gsm;
    protected ResourceManager resources;

    protected Screen(GameScreenManager gsm, ResourceManager resources) {
        this.gsm = gsm;
        this.resources = resources;
        camera = new OrthographicCamera();
        viewport = new FitViewport(MyGame.V_WIDTH, MyGame.V_HEIGHT, camera);
        mousePosition = new Vector3();
        SCREEN_SIZE = new Vector2 (MyGame.V_WIDTH, MyGame.V_HEIGHT);
    }

    protected abstract void inputHandler();

    protected abstract void update(float dt);

    protected abstract void render(SpriteBatch batch);

    public abstract void dispose();
}