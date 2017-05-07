import 'dart:html';
import 'dart:math';
import 'dart:async';
import 'dart:collection';

class Keyboard
{
    final HashSet<int> _keys = new HashSet<int>();
    Keyboard()
    {
        window.onKeyDown.listen((final KeyboardEvent e)
        {
            _keys.add(e.keyCode);
        });
        window.onKeyUp.listen((final KeyboardEvent e)
        {
            _keys.remove(e.keyCode);
        });
    }
    isPressed(final int keyCode) => _keys.contains(keyCode);
}

class GameHost
{
    final CanvasElement _canvas;
    final Keyboard _keyboard = new Keyboard();

    int _lastTimestamp = 0;
    double _x = 400.0;
    double _y = 300.0;

    GameHost(this._canvas);

    run()
    {
        window.requestAnimationFrame(_gameLoop);
    }

    void _gameLoop(final double _)
    {
        _update(_getElapsed());
        _render();
        window.requestAnimationFrame(_gameLoop);
    }

    double _getElapsed()
    {
        final int time = new DateTime.now().millisecondsSinceEpoch;

        double elapsed = 0.0;
        if (_lastTimestamp != 0)
        {
            elapsed = (time - _lastTimestamp) / 1000.0;
        }

        _lastTimestamp = time;
        return elapsed;
    }

    void _update(final double elapsed)
    {
        final double velocity = 100.0;

        if (_keyboard.isPressed(KeyCode.UP))    _y -= velocity * elapsed;
        if (_keyboard.isPressed(KeyCode.DOWN))  _y += velocity * elapsed;
        if (_keyboard.isPressed(KeyCode.LEFT))  _x -= velocity * elapsed;
        if (_keyboard.isPressed(KeyCode.RIGHT)) _x += velocity * elapsed;
    }

    void _render()
    {
        final CanvasRenderingContext2D context = _canvas.context2D;

        context..globalAlpha = 1
               ..fillStyle = "white"
               ..beginPath()
               ..rect(0, 0, 800, 600)
               ..fill();

        context..beginPath()
               ..fillStyle = "black"
               ..arc(_x, _y, 32, 0, PI * 2.0)
               ..fill();
    }
}

void main()
{
    final CanvasElement canvas = querySelector("#area");
    canvas.focus();
    scheduleMicrotask(new GameHost(canvas).run);
}