#ifndef HIDEFLAGS_H
#define HIDEFLAGS_H




namespace JuliEngine
{
    //
    // Resumen:
    //     Bit mask that controls object destruction, saving and visibility in inspectors.
    enum HideFlags
    {
        //
        // Resumen:
        //     A normal, visible object. This is the default.
        None = 0,
        //
        // Resumen:
        //     The object will not appear in the hierarchy.
        HideInHierarchy = 1,
        //
        // Resumen:
        //     It is not possible to view it in the inspector.
        HideInInspector = 2,
        //
        // Resumen:
        //     The object will not be saved to the Scene in the editor.
        DontSaveInEditor = 4,
        //
        // Resumen:
        //     The object is not editable in the Inspector.
        NotEditable = 8,
        //
        // Resumen:
        //     The object will not be saved when building a player.
        DontSaveInBuild = 16,
        //
        // Resumen:
        //     The object will not be unloaded by Resources.UnloadUnusedAssets.
        DontUnloadUnusedAsset = 32,
        //
        // Resumen:
        //     The object will not be saved to the Scene. It will not be destroyed when a new
        //     Scene is loaded. It is a shortcut for HideFlags.DontSaveInBuild | HideFlags.DontSaveInEditor
        //     | HideFlags.DontUnloadUnusedAsset.
        DontSave = 52,
        //
        // Resumen:
        //     The GameObject is not shown in the Hierarchy, not saved to to Scenes, and not
        //     unloaded by Resources.UnloadUnusedAssets.
        HideAndDontSave = 61
    };
}

#endif // !HIDEFLAGS_H
