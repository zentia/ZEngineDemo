// P7 smoke script. Used by docs/TYPESCRIPT_SCRIPTING_DESIGN.md acceptance for
// Phase 7 (per-instance serialised field overrides):
//
//   1. Inspector -> "Add TypeScript Behaviour" -> P7Smoke.
//   2. The "Script Fields" section under the component shows three rows:
//        speed   (number)   default 1.5
//        enabled (boolean)  default true
//        label   (string)   default "hi"
//      Each rendered with the matching widget (InputDouble / Checkbox /
//      InputText). The leading-underscore field `_ticks` is intentionally
//      hidden by the shim's filter.
//   3. Edit speed=4.2, label="changed", uncheck enabled. ZEditor logs
//      (under [ZScripting]):
//        "P7Smoke.OnUpdate speed=4.2 enabled=false label=changed"
//   4. Save the scene, restart ZEditor: edits survive (m_serialized_fields
//      round-tripped). On startup the Inspector shows the persisted values.
//   5. Save P7Smoke.ts (no logical change) to trigger hot-reload: the live
//      JS instance is rebuilt; OnAwake fires again; the previously edited
//      values still show in the Inspector and in the OnUpdate log line.
export class P7Smoke extends Behaviour {
    speed: number = 1.5;
    enabled: boolean = true;
    label: string = "hi";

    private _ticks = 0;

    OnAwake(): void {
        console.log(`P7Smoke.OnAwake speed=${this.speed} enabled=${this.enabled} label=${this.label}`);
    }

    OnUpdate(dt: number): void {
        if ((this._ticks++ % 60) === 0) {
            console.log(`P7Smoke.OnUpdate speed=${this.speed} enabled=${this.enabled} label=${this.label}`);
        }
    }
}
