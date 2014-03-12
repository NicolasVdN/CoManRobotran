
#ifdef SIMBODY

#include "cmake_config.h"
#include "simbody_cpp_functions.hpp"

int init_Simbody(SimbodyVariables *p_simbodyVariables, SimbodyBodiesStruct *p_simbodyBodiesStruct)
{

	// set all the mechanical parameters of the contact
	const Real ud = 0.9; // dynamic   dry friction coefficient- it is the same as in your GCM
    const Real us = 1.1; // static;  it is required ud < us
    const Real uv = 0;  // viscous (force/velocity)
    const Real c = 0.1;//3.3; // dissipation (1/v)
	const Real BoxMass = 1.0;	 // kg -> not used
	const Real k = 1e5; // pascals 

	MultibodySystem *p_system = p_simbodyVariables->p_system;
	SimbodyMatterSubsystem *p_matter = p_simbodyVariables->p_matter;
	State *p_state = p_simbodyVariables->p_state;

// that part of the code means that there is a ground z = 0;	
	const Rotation R_zdown(Pi/2.,YAxis);
	p_matter->Ground().updBody().addContactSurface(
        Transform(R_zdown, Vec3(0,0,0)),
        ContactSurface(ContactGeometry::HalfSpace(),
                       ContactMaterial(k,c,us,ud,uv))); // here we add ground "z+" - is available halfspace.
   
// that is a geometrical parameters of the body - it is important 
	double zwidth = 0.01;
	const Vec3 halfDims(0.095, 0.05, zwidth); // halfDims are the halves of the Box sides
    const Vec3 comLoc(0, 0, 0);  // Location of the center of mass

// set the mass-inertial properties of the body. This parameters might be arbitrary
	const Inertia centralInertia(Vec3(17,2,16), Vec3(0,0,.2)); // 
 	Body::Rigid LeftFootBody(MassProperties(BoxMass, comLoc, centralInertia));
	
    /*
	//creates a bordering boxes for left foot
	Real wantEdgeLength = 0.1;
    int resolution = (int)(max(halfDims)/wantEdgeLength + 0.5);
	//resolution = 2;
	ContactGeometry::TriangleMesh LeftFootTrM(PolygonalMesh::createBrickMesh(halfDims,resolution)); 
	ContactGeometry::TriangleMesh RightFootTrM(PolygonalMesh::createBrickMesh(halfDims,resolution)); 
	std::cout<<"faces = "<<LeftFootTrM.getNumFaces();
// 5 - is a resolution of the mesh,
//For this shape, resolution is interpreted as the number of extra vertices to insert in the longest 
//edge of the brick. Extra vertices are inserted into the shorter edges if needed to keep the edge lengths 
//approximately uniform for every mesh face. resolution=0 gives only vertices at the corners; the default is 
// 1 meaning that the longest edge is split once. 
	double shift =  0.035;
	LeftFootBody.addContactSurface(Transform(Vec3(shift,0,zwidth)),
							   ContactSurface(LeftFootTrM,
											   ContactMaterial(k,c,us,ud,uv),
											   0.001) // thickness, it is a parameter of the Compliant Contact - thickness of the layer of springs
											   );

// add the border to a BoxBody
//*/
	// creates a mesh for left foot:
	std::ifstream meshFile1;
	PolygonalMesh LeftFootMesh;
		printf("Open left");
	//meshFile1.open("./src/project/Simbody_mesh/left_foot.obj"); 
		meshFile1.open(PROJECT_ABS_PATH"/src/generic/simbody/left_foot.obj"); 
		printf("Open left %i",meshFile1.is_open());
	LeftFootMesh.loadObjFile(meshFile1); 
		printf("Open left");
	meshFile1.close();

		
// apply a contactGeometry for left foot
	ContactGeometry::TriangleMesh LeftFootTrM(LeftFootMesh); 
	std::cout<<"faces = "<<LeftFootTrM.getNumFaces();
	LeftFootBody.addContactSurface(Transform(Vec3(0,0,0)),
							   ContactSurface(LeftFootTrM,
											   ContactMaterial(k,c,us,ud,uv),
											   0.001) // thickness, it is a parameter of the Compliant Contact - thickness of the layer of springs
											   );//*/


	// it is only for visualization.
// 	DecorativeMesh showBox(box.createPolygonalMesh());  
//	BoxBody.addDecoration(Transform(), 
//							showBox.setColor(Red).setOpacity(1));

// creates Box - an instance of the BoxBody, it has 6 DOF
    MobilizedBody::Free LeftFoot(p_matter->Ground(), Transform(Vec3(0,0,0)),
        LeftFootBody, Transform(Vec3(0)));

	// old: // p_simbodyVariables->BodyInd=Box.getMobilizedBodyIndex(); // it is useful to store the indexes of the created bodies, especially when we have more than one
	p_simbodyBodiesStruct->Simbody_index[0] = LeftFoot.getMobilizedBodyIndex(); // Z: I store the indexes of the bodies in the simbodyBodiesStruct

	// creates a body dor RightFoot
	Body::Rigid RightFootBody(MassProperties(BoxMass, comLoc, centralInertia));

	/*
	//creates a bordering boxes for left foot
	RightFootBody.addContactSurface(Transform(Vec3(shift,0,zwidth)),
							   ContactSurface(RightFootTrM,
											   ContactMaterial(k,c,us,ud,uv),
											   0.001) // it is a parameter of the Compliant Contact - thicknes of the layer of springs
											   );//*/
	
	
	// creates a mesh for right foot:
	std::ifstream meshFile2;
	PolygonalMesh RightFootMesh;
	meshFile2.open(PROJECT_ABS_PATH"/src/generic/simbody/right_foot.obj"); 
	printf("Open right %i",meshFile2.is_open());
	RightFootMesh.loadObjFile(meshFile2); 
	printf("Open right");
	meshFile2.close();
		printf("Open right");
// apply a contactGeometry for left foot
	ContactGeometry::TriangleMesh RightFootTrM(RightFootMesh); 
	// apply a contactGeometry for left foot
	
	RightFootBody.addContactSurface(Transform(Vec3(0,0,0)),
							   ContactSurface(LeftFootTrM,
											   ContactMaterial(k,c,us,ud,uv),
											   0.001) // thickness, it is a parameter of the Compliant Contact - thickness of the layer of springs
											   );//*/
	
	
// it is only for visualization.
// 	DecorativeMesh showBox(box.createPolygonalMesh());  
//	BoxBody.addDecoration(Transform(), 
//							showBox.setColor(Red).setOpacity(1));

// creates Box - an instance of the BoxBody, it has 6 DOF
    MobilizedBody::Free RightFoot(p_matter->Ground(), Transform(Vec3(0,0,0)),
        RightFootBody, Transform(Vec3(0)));

	p_simbodyBodiesStruct->Simbody_index[1] = RightFoot.getMobilizedBodyIndex(); // Z: I store the indexes of the bodies in the simbodyBodiesStruct

	
 return 0;
}

int loop_Simbody (SimbodyVariables *p_simbodyVariables, SimbodyBodiesStruct* simbodyBodiesStruct) 
{	
	
    ContactForce CF;

    int index;

    int i;
    
	int ContCount;
	// I'm getting all the system variables 
	MultibodySystem *p_system = p_simbodyVariables->p_system;
	SimbodyMatterSubsystem *p_matter = p_simbodyVariables->p_matter;
	ContactTrackerSubsystem  *p_tracker = p_simbodyVariables->p_tracker; 
    CompliantContactSubsystem *p_contactForces = p_simbodyVariables->p_contactForces;
    State* p_state = p_simbodyVariables->p_state;
	
	
	// stage 1: to  update all the cinematic variables for all the bodies in the system

	for(i=0;i<NB_CONTACT_BODIES;i++)
	{
	  MobilizedBodyIndex BodyInd = (MobilizedBodyIndex) simbodyBodiesStruct->Simbody_index[i]; // for each body in the Simbody_index aray
	  const MobilizedBody Box=p_matter->getMobilizedBody(BodyInd); // get the object MobilizedBody 
	  index = i;
	  //to set the coordinates to the bodies, they are stored in Cinematic parameters structure
	   Box.setQToFitTransform(*p_state, Transform(Vec3(simbodyBodiesStruct->abs_pos_CoM[index])));
	   Box.setUToFitLinearVelocity (*p_state, Vec3(simbodyBodiesStruct->lin_vel_CoM[index]));
	   Box.setUToFitAngularVelocity (*p_state, Vec3(simbodyBodiesStruct->ang_vel_CoM[index]));

	    const Mat<3,3,Real> M(simbodyBodiesStruct->rot_matrix[index][0] , simbodyBodiesStruct->rot_matrix[index][1] , simbodyBodiesStruct->rot_matrix[index][2],
	                      simbodyBodiesStruct->rot_matrix[index][3] , simbodyBodiesStruct->rot_matrix[index][4] , simbodyBodiesStruct->rot_matrix[index][5],
		                  simbodyBodiesStruct->rot_matrix[index][6] , simbodyBodiesStruct->rot_matrix[index][7] , simbodyBodiesStruct->rot_matrix[index][8]);
	    const Rotation RotMatr(M, true);
	    const Rotation NewRotMatr=RotMatr.invert();
	    Box.setQToFitRotation(*p_state, NewRotMatr);
		p_system->realize(*p_state,Stage::Dynamics);
		Rotation RBR = Box.getBodyRotation(*p_state);
	//	if (RBR == NewRotMatr) printf ("\n Success! "); 
	//	else 
	//	{
	//		printf ("\n Fail! \n");
	/*	double err =0;	
		for (int i1=0;i1<3;i1++)
			{
			  for (int j1=0;j1<3;j1++)
			  {
				//printf ("%lf != %lf ",NewRotMatr[i1][j1],RBR[i1][j1]);
				err += NewRotMatr[i1][j1] - RBR[i1][j1];
			  }
			  printf ("\n");
			} */
	//	printf ("err = %.9lf \n ", err);
		
	
		// to be sure, that without contact all the forces equals zero:		
		for(int j=0; j<3; j++)
		{
				simbodyBodiesStruct->force_bodies[i][j]  = 0.0;
				simbodyBodiesStruct->torque_bodies[i][j] = 0.0;
		} 
	}


//"system" operations - on this stage it computes all the active contacts 	
	p_system->realize(*p_state,Stage::Dynamics);
	p_state->autoUpdateDiscreteVariables();	
	
	//I'm getting the information about Active Contacts
	int NumofCont = p_contactForces->getNumContactForces(*p_state);
	//printf("I'm here 0 \n");     
	ContactSnapshot CS=p_tracker->getActiveContacts(*p_state);
	//printf("NumofCont = %d > \n",NumofCont);
	
	for (ContCount=0; ContCount < NumofCont; ++ContCount) 
	{
     // printf("I'm here 1 \n");     
		//for each contact we compute the force	 
     // printf("Cont = %d > ",ContCount);
      //Get the total spatial force applied to body 2 at the contact point (that is, a force and a moment); 
   // negate this to find the force applied to body 1 at the same point.    	 
	 const ContactForce& force = p_contactForces->getContactForce(*p_state,ContCount);
	 //retrieving information about the contact if we need it
   	 // Contact CurContact=CS.getContact(ContCount);
	 //cout<<"Contact Condition"<<CurContact.getCondition()<<"\n"; // to get Condition of the Contact: 
	 // Unknown - this is an illegal value
	 //Untracked - this pair not yet being tracked; might not contact
     //Anticipated - we expect these to contact soon
     //NewContact - first time seen; needs a ContactId assigned
     //Ongoing 	was new or ongoing before; still in contact now
     //Broken 	was new or ongoing before; no longer in contact 
	// printf("I'm here 2 \n");     
	  const ContactId     id    = force.getContactId();
      const Vec3 frc = force.getForceOnSurface2()[1];
      const Vec3 mom = force.getForceOnSurface2()[0];
	  const Vec3 AP = force.getContactPoint(); // that are coordinates of the Application Point in fixed coordinate frame
// the following part of code gets information - which bodies of the system are in contact. 
// If bodies are non-convex there might be two Surfaces that belong to this body in contact, so we should sum the forces on this surfaces.
      Contact CurCont = CS.getContactById(id);
	  ContactSurfaceIndex Surf1 = CurCont.getSurface1();
	  ContactSurfaceIndex Surf2 = CurCont.getSurface2();
	  const MobilizedBody Body1 = p_tracker->getMobilizedBody(Surf1);
	  const MobilizedBody Body2 = p_tracker->getMobilizedBody(Surf2);
	  MobilizedBodyIndex Body1Ind = Body1.getMobilizedBodyIndex();
	  MobilizedBodyIndex Body2Ind = Body2.getMobilizedBodyIndex();
	  const Vec3& CP2 = AP - Body2.findMassCenterLocationInGround(*p_state);
	  const Vec3& CP1 = AP - Body1.findMassCenterLocationInGround(*p_state);

// output to Robotran: FonB1 - force on the first body, FonB2 - force on the second body 
      for(i=0;i<NB_CONTACT_BODIES;i++)	
	  {
		  if (Body2Ind == simbodyBodiesStruct->Simbody_index[i])
		  {
			  /*printf("i = %d > ",i);*/
	  	      //printf("CP2 = %f  %f %f > \n",CP2[0],CP2[1],CP2[2]);//*/
			  //printf("AP = %f  %f %f > \n",AP[0],AP[1],AP[2]);//*/
			  
			  
			  
			  simbodyBodiesStruct->force_bodies[i][0]  += frc[0];
			  simbodyBodiesStruct->force_bodies[i][1]  += frc[1];
			  simbodyBodiesStruct->force_bodies[i][2]  += frc[2];
		     
			  simbodyBodiesStruct->torque_bodies[i][0] +=  mom[0] + CP2[1]*frc[2] - CP2[2]*frc[1]; 
	          simbodyBodiesStruct->torque_bodies[i][1] +=  mom[1] + CP2[2]*frc[0] - CP2[0]*frc[2];
	          simbodyBodiesStruct->torque_bodies[i][2] +=  mom[2] + CP2[0]*frc[1] - CP2[1]*frc[0];	  //*/
			  
			  /*printf("\n CM = %f  %f %f > \n",Body2.findMassCenterLocationInGround(*p_state)[0],Body2.findMassCenterLocationInGround(*p_state)[1],Body2.findMassCenterLocationInGround(*p_state)[2]);
			  printf("\n M = %f  %f %f > \n",simbodyBodiesStruct->torque_bodies[i][0],simbodyBodiesStruct->torque_bodies[i][1],simbodyBodiesStruct->torque_bodies[i][2]);
			  printf("\n F = %f  %f %f > \n",simbodyBodiesStruct->force_bodies[i][0],simbodyBodiesStruct->force_bodies[i][1],simbodyBodiesStruct->force_bodies[i][2]);
			  printf("\n AP = %f  %f %f > \n",AP[0],AP[1],AP[2]);
			  printf("\n mom = %f  %f %f > \n",mom[0],mom[1],mom[2]); 
			  printf("\n CP2 = %f  %f %f > \n",CP2[0],CP2[1],CP2[2]); 
			  Vec3 ex = Body2.expressVectorInAnotherBodyFrame(*p_state,Vec3(1,0,0),p_matter->getGround());
			  printf("\n ex = %f  %f %f > \n",ex[0],ex[1],ex[2]); 
			  getchar();//*/

			 /* simbodyBodiesStruct->force_bodies[i][0]  = frc[0];
			  simbodyBodiesStruct->force_bodies[i][1]  = frc[1];
			  simbodyBodiesStruct->force_bodies[i][2]  = frc[2];
		     
			  simbodyBodiesStruct->torque_bodies[i][0] = mom[0]; 
	          simbodyBodiesStruct->torque_bodies[i][1] = mom[1];
	          simbodyBodiesStruct->torque_bodies[i][2] = mom[2];	  
			  
			  simbodyBodiesStruct->AP[i][0] = AP[0]; 
	          simbodyBodiesStruct->AP[i][1] = AP[1];
	          simbodyBodiesStruct->AP[i][2] = AP[2];	  */
			  

			//  printf("M = %f  %f %f > \n",simbodyBodiesStruct->torque_bodies[i][0],simbodyBodiesStruct->torque_bodies[i][1],simbodyBodiesStruct->torque_bodies[i][2]);//*/
	  	  }
		  if (Body1Ind == simbodyBodiesStruct->Simbody_index[i])
		  {
			  // printf("i = %d > ",i);
			  simbodyBodiesStruct->force_bodies[i][0]  += -frc[0];
			  simbodyBodiesStruct->force_bodies[i][1]  += -frc[1];
			  simbodyBodiesStruct->force_bodies[i][2]  += -frc[2];
		     
			  simbodyBodiesStruct->torque_bodies[i][0] += -mom[0] - CP1[1]*frc[2] + CP1[2]*frc[1];  
	          simbodyBodiesStruct->torque_bodies[i][1] += -mom[1] - CP1[2]*frc[0] + CP1[0]*frc[2];
	          simbodyBodiesStruct->torque_bodies[i][2] += -mom[2] - CP1[0]*frc[1] + CP1[1]*frc[0];//*/
			 
			  /*simbodyBodiesStruct->force_bodies[i][0]  = - frc[0];
			  simbodyBodiesStruct->force_bodies[i][1]  = - frc[1];
			  simbodyBodiesStruct->force_bodies[i][2]  = - frc[2];
		     
			  simbodyBodiesStruct->torque_bodies[i][0] = - mom[0]; 
	          simbodyBodiesStruct->torque_bodies[i][1] = - mom[1];
	          simbodyBodiesStruct->torque_bodies[i][2] = - mom[2];	  
	

			  simbodyBodiesStruct->AP[i][0] = AP[0]; 
	          simbodyBodiesStruct->AP[i][1] = AP[1];
	          simbodyBodiesStruct->AP[i][2] = AP[2];	  */
	
	  	  }
	  }
	}
   return 0;
}

#endif
