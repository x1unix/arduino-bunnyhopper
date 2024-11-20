(() => {
  'use strict';
  const useTextContent = (selector, onBefore) => {
    const e = document.querySelector(selector);
    return (content) => {
      if (onBefore) {
        onBefore(e);
      }

      e.textContent = String(content);
    }
  }

  const highlightAnimation = {
    keyframes: [
      {
        background: 'var(--color-text-muted)'
      },
      {
        background: 'transparent'
      }
    ],
    params: {
      duration: 175,
    },
  };

  const setKps = useTextContent('#kps');
  const setDeltaTime = useTextContent('#delta-time');
  const setLastKey = useTextContent('#last-key', (e) => {
    const { keyframes, params } = highlightAnimation
    e.animate(keyframes, params);
  });

  const stats = {
    prevKeyTime: 0,
    keyPressCount: 0,
  };

  const updateKpsCounter = () => {
    const kps = stats.keyPressCount;
    stats.keyPressCount = 0;
    setKps(kps);
    if (kps === 0) {
      stats.prevKeyTime = 0;
      setDeltaTime(0);
    }

    setTimeout(updateKpsCounter, 1000);
  }

  const onKeyDown = (event) => {
    setLastKey(event.code);

    const now = Date.now();
    if (stats.prevKeyTime !== 0) {
      const delta = now - stats.prevKeyTime;
      setDeltaTime(delta);
    }

    stats.prevKeyTime = now;
    stats.keyPressCount++;
  }


  document.body.addEventListener('keydown', onKeyDown);
  updateKpsCounter();
})()
