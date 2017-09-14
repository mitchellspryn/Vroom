#ifndef VROOM_JSONUTILITIES_H
#define VROOM_JSONUTILITIES_H

static class JsonUtilities
{
	public:
		template <class T>
		static void SetIfExists(T* prop, const char* propertyName, const rapidjson::Value& json)
		{
			if (json.HasMember(propertyName))
			{
				SetInternal(prop, propertyName, json);
			}
		}

		static void ParseRuntimeFloatCurveIfExists(
			FRuntimeFloatCurve& curve,
			const rapidjson::Value &data,
			const char* propertyName,
			const ERichCurveInterpMode interpMode = RCIM_Linear,
			const char* xValue = "x",
			const char* yValue = "y",
			const char* curveName = "Dummy")
		{
			if (data.HasMember(propertyName))
			{
				ParseRuntimeFloatCurve(curve, data[propertyName], interpMode, xValue, yValue, curveName);
			}
		}

		/*Expect data to point to array of ["x", "y"] tuples*/
		static void ParseRuntimeFloatCurve(
			FRuntimeFloatCurve& curve,
			const rapidjson::Value &data,
			const ERichCurveInterpMode interpMode = RCIM_Linear,
			const char* xValue = "x",
			const char* yValue = "y",
			const char* curveName = "Dummy")
		{
			auto richCurve = new FRichCurve();

			for (auto &v : data.GetArray())
			{
				float x = v[xValue].GetFloat();
				float y = v[yValue].GetFloat();
				auto key = richCurve->AddKey(x, y);
				richCurve->SetKeyInterpMode(key, interpMode);
			}

			auto curveFloat = NewObject<UCurveFloat>();
			auto list = curveFloat->GetCurves();
			list.Add(FRichCurveEditInfo(richCurve, FName(curveName)));

			curve.ExternalCurve = curveFloat;

			/*Let unreal know that the curve has been modified*/
			curve.ExternalCurve->Modify(true);
		}

	private:
		static void SetInternal(bool* prop, const char* propertyName, const rapidjson::Value& json)
		{
			*prop = json[propertyName].GetBool();
		}

		//Apparently this overload will be called for int32 as well 
		//In any case, defining overload for int32* causes compilation error ¯\_(ツ)_/¯
		static void SetInternal(int* prop, const char* propertyName, const rapidjson::Value& json)
		{
			*prop = json[propertyName].GetInt();
		}

		static void SetInternal(std::string* prop, const char* propertyName, const rapidjson::Value& json)
		{
			*prop = json[propertyName].GetString();
		}

		static void SetInternal(float* prop, const char* propertyName, const rapidjson::Value& json)
		{
			*prop = json[propertyName].GetFloat();
		}

		static void SetInternal(double* prop, const char* propertyName, const rapidjson::Value &json)
		{
			*prop = json[propertyName].GetDouble();
		}
};


#endif