// P4 acceptance test: prove that ScriptingManager.LoadModule()
// successfully runs an .ts module and that the console / Debug
// globals route through to ZEngine's logger (ZScripting log category).
//
// Loaded automatically by EditorApplication's startup scan because
// the .js sits in <project>/Intermediate/Scripts/.
//
// Hello.ts itself is reserved for the P5 (Behaviour subclass) demo,
// so we keep this one stand-alone and free of engine dependencies.

console.log("[P4Smoke] hi from TypeScript module");
console.info("[P4Smoke] console.info works");
console.warn("[P4Smoke] console.warn works");

if (typeof Debug !== "undefined") {
    Debug.Log("[P4Smoke] Debug.Log works");
    Debug.LogWarning("[P4Smoke] Debug.LogWarning works");
}

// Export something so the loader has a non-empty module.exports.
export const P4_SMOKE_OK: boolean = true;

export function ping(): string {
    return "pong";
}
