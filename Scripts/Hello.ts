// P5 smoke script. Used by docs/TYPESCRIPT_SCRIPTING_DESIGN.md acceptance:
//   1. Inspector -> "Add TypeScript Behaviour" -> Hello
//   2. ZEditor logs (under [ZScripting]):
//        - module loaded: Hello
//        - "Hello.OnAwake"
//        - "Hello.OnStart"
//        - one "Hello.OnUpdate dt=<small float>" per frame
//   3. Saving a change re-emits Intermediate/Scripts/Hello.js -> hot-reload.
export class Hello extends Behaviour {
    private _ticks = 0;

    OnAwake(): void {
        console.log("Hello.OnAwake");
    }

    OnStart(): void {
        console.log("Hello.OnStart");
    }

    OnUpdate(dt: number): void {
        // Throttle the per-frame log so we don't drown the console.
        if ((this._ticks++ % 60) === 0) {
            console.log(`Hello.OnUpdate dt=${dt.toFixed(4)} tick=${this._ticks}`);
        }
    }

    OnDestroy(): void {
        console.log("Hello.OnDestroy");
    }
}
