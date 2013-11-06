


exception ServiceUnavailable {

	1: i32 error_code,
	2: string error_message
}


struct MoxelRepresentation {
	
	1: double x,
	2: double y,
	3: double z,
}

struct MoxelSpace {
	
	1: list<MoxelRepresentation> moxels,
}

service Aether {
	
	MoxelSpace get_moxel_snapshot() throws (1:ServiceUnavailable sunav)
}







